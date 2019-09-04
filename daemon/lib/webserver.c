#include <webserver.h>
#include <webchars.h>
#ifdef _MSC_VER
#ifndef strcasecmp
#define strcasecmp(a,b) _stricmp((a),(b))
#endif /* !strcasecmp */
#endif /* _MSC_VER */

#if defined(_MSC_VER) && _MSC_VER+0 <= 1800
/* Substitution is OK while return value is not used */
#define snprintf _snprintf
#endif

#define POSTBUFFERSIZE  512
#define MAXCLIENTS      100

const char *askpage = askpage_html;

const char *busypage = busypage_html;

const char *completepage = completepage_html;

const char *errorpage = errorpage_html;

const char *servererrorpage = servererrorpage_html;

const char *fileexistspage = fileexistspage_html;

const char *fileioerror = fileioerror_html;

const char* const postprocerror = postprocerror_html;

enum ConnectionType{
  GET = 0,
  POST = 1
};

static unsigned int nr_of_uploading_clients = 0;


/**
* Information we keep per connection.
*/
struct connection_info_struct{
  enum ConnectionType connectiontype;

  /**
  * Handle to the POST processing state.
  */
  struct MHD_PostProcessor *postprocessor;

  /**
  * File handle where we write uploaded data.
  */
  FILE *fp;

  /**
  * HTTP response body we will return, NULL if not yet known.
  */
  const char *answerstring;

  /**
  * HTTP status code we will return, 0 for undecided.
  */
  unsigned int answercode;


  //This is a modified segment
  config* conf;
  char filename[256];

};


int send_page (struct MHD_Connection *connection,
           const char *page,
           int status_code) {
  int ret;
  struct MHD_Response *response;

  response = MHD_create_response_from_buffer (strlen (page), (void *) page, MHD_RESPMEM_MUST_COPY);
  if (!response) return MHD_NO;
  MHD_add_response_header (response, MHD_HTTP_HEADER_CONTENT_TYPE, "text/html");
  ret = MHD_queue_response (connection, status_code, response);
  MHD_destroy_response (response);

  return ret;
}


int iterate_post (void *coninfo_cls,
              enum MHD_ValueKind kind,
              const char *key,
              const char *filename,
              const char *content_type,
              const char *transfer_encoding,
              const char *data,
              uint64_t off,
              size_t size){
  struct connection_info_struct *con_info = coninfo_cls;
  FILE *fp;
  (void)kind;               /* Unused. Silent compiler warning. */
  (void)content_type;       /* Unused. Silent compiler warning. */
  (void)transfer_encoding;  /* Unused. Silent compiler warning. */
  (void)off;                /* Unused. Silent compiler warning. */

  //Make path for original image
  char filepath[256];
  sprintf(filepath, "%s%s", con_info->conf->dirorg, filename);

  if (0 != strcmp (key, "file")){
    con_info->answerstring = servererrorpage;
    con_info->answercode = MHD_HTTP_BAD_REQUEST;
    return MHD_YES;
  }

  if (!con_info->fp){
    if (0 != con_info->answercode) /* something went wrong */
      return MHD_YES;
    if (NULL != (fp = fopen (filepath, "rb"))){
      fclose (fp);
      con_info->answerstring = fileexistspage; //Here returns if file exists already
      con_info->answercode = MHD_HTTP_FORBIDDEN;
      return MHD_YES;
    }

    strcpy(con_info->filename, filename);
    con_info->fp = fopen (filepath, "ab");
    if (!con_info->fp){
      con_info->answerstring = fileioerror;
      con_info->answercode = MHD_HTTP_INTERNAL_SERVER_ERROR;
      return MHD_YES;
    }


    //New post
  }

  if (size > 0){
    if (! fwrite (data, sizeof (char), size, con_info->fp))
    {
      con_info->answerstring = fileioerror;
      con_info->answercode = MHD_HTTP_INTERNAL_SERVER_ERROR;
      return MHD_YES;
    }
  }

  return MHD_YES;
}


void request_completed (void *cls,
                   struct MHD_Connection *connection,
                   void **con_cls,
                   enum MHD_RequestTerminationCode toe){
  struct connection_info_struct *con_info = *con_cls;
  (void)cls;         /* Unused. Silent compiler warning. */
  (void)connection;  /* Unused. Silent compiler warning. */
  (void)toe;         /* Unused. Silent compiler warning. */

  if (NULL == con_info)
    return;

  if (con_info->connectiontype == POST){
    if (NULL != con_info->postprocessor){
      MHD_destroy_post_processor (con_info->postprocessor);
      nr_of_uploading_clients--;
    }

    if (con_info->fp)
      fclose (con_info->fp);
  }

  free (con_info);
  *con_cls = NULL;
}


int answer_to_connection (void *cls,
                      struct MHD_Connection *connection,
                      const char *url,
                      const char *method,
                      const char *version,
                      const char *upload_data,
                      size_t *upload_data_size,
                      void **con_cls){
  config* conf = (config*)cls;            
  (void)url;               /* Unused. Silent compiler warning. */
  (void)version;           /* Unused. Silent compiler warning. */

  if (NULL == *con_cls){
    /* First call, setup data structures */
    struct connection_info_struct *con_info;
    if (nr_of_uploading_clients >= MAXCLIENTS)
      return send_page (connection,
                        busypage,
                        MHD_HTTP_SERVICE_UNAVAILABLE);

    con_info = malloc (sizeof (struct connection_info_struct));
    if (NULL == con_info)
      return MHD_NO;
    con_info->answercode = 0; /* none yet */
    con_info->fp = NULL;
    con_info->conf = conf; //modified
    if (0 == strcasecmp (method, MHD_HTTP_METHOD_POST)){
      con_info->postprocessor =
        MHD_create_post_processor (connection,
                                   POSTBUFFERSIZE,
                                   &iterate_post,
                                   (void *) con_info);

      if (NULL == con_info->postprocessor){
        free (con_info);
        return MHD_NO;
      }

      nr_of_uploading_clients++;

      con_info->connectiontype = POST;
    }
    else{
      con_info->connectiontype = GET;
    }

    *con_cls = (void *) con_info;

    return MHD_YES;
  }

  if (0 == strcasecmp (method, MHD_HTTP_METHOD_GET)){
    /* We just return the standard form for uploads on all GET requests */
    char buffer[1024];

    snprintf (buffer,
              sizeof (buffer),
              askpage,
              nr_of_uploading_clients);
    return send_page (connection,
                      buffer,
                      MHD_HTTP_OK);
  }

  if (0 == strcasecmp (method, MHD_HTTP_METHOD_POST)){
    struct connection_info_struct *con_info = *con_cls;

    if (0 != *upload_data_size){
      /* Upload not yet done */
      if (0 != con_info->answercode){
        /* we already know the answer, skip rest of upload */
        *upload_data_size = 0;
        return MHD_YES;
      }
      if (MHD_YES !=
          MHD_post_process (con_info->postprocessor,
                            upload_data,
                            *upload_data_size)){
        con_info->answerstring = postprocerror;
        con_info->answercode = MHD_HTTP_INTERNAL_SERVER_ERROR;
      }
      *upload_data_size = 0;

      return MHD_YES;
    }
    /* Upload finished */
    if (NULL != con_info->fp){
      fclose (con_info->fp);
      con_info->fp = NULL;
    }
    if (0 == con_info->answercode){
      /* No errors encountered, declare success */
      con_info->answerstring = completepage;
      con_info->answercode = MHD_HTTP_OK;

      //This calls an end to the transfer
      completeTransfer(con_info->filename, conf);
    }
    return send_page (connection,
                      con_info->answerstring,
                      con_info->answercode);
  }

  /* Note a GET or a POST, generate error */
  return send_page (connection,
                    errorpage,
                    MHD_HTTP_BAD_REQUEST);
}

void startTransfer(char* filename, config* conf){

}

void completeTransfer(char* filename, config* conf){

  char buffer[256];
  sprintf(buffer, "Completed transfer of file: %s\n", filename);
  append_file(conf->dirlog, buffer);

  histogram(conf->dirorg, filename, conf->dirclas);
  classify(conf->dirorg, filename, conf->dirclas);
  
}

//Pass the config value

struct MHD_Daemon* startServer(config* conf) {
  struct MHD_Daemon* daemon;

  daemon = MHD_start_daemon (MHD_USE_INTERNAL_POLLING_THREAD,
                             conf->port, NULL, NULL,
                             &answer_to_connection, conf,
                             MHD_OPTION_NOTIFY_COMPLETED, &request_completed, NULL,
                             MHD_OPTION_END);
  return daemon;
}

void stopDaemon(struct MHD_Daemon* daemon){
  MHD_stop_daemon (daemon);
}