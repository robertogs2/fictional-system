// webserver.h

#ifndef _WEBSERVER_H
#define _WEBSERVER_H

#include <sys/types.h>

#ifndef _WIN32
#include <sys/select.h>
#include <sys/socket.h>
#else
#include <winsock2.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

typedef struct {
    int port;
    char dirlog[100];
    char dirhist[100];
    char dirclas[100];
} config;

int iterate_post (void *coninfo_cls,
              enum MHD_ValueKind kind,
              const char *key,
              const char *filename,
              const char *content_type,
              const char *transfer_encoding,
              const char *data,
              uint64_t off,
              size_t size);
void request_completed (void *cls,
                   struct MHD_Connection *connection,
                   void **con_cls,
                   enum MHD_RequestTerminationCode toe);
int answer_to_connection (void *cls,
                      struct MHD_Connection *connection,
                      const char *url,
                      const char *method,
                      const char *version,
                      const char *upload_data,
                      size_t *upload_data_size,
                      void **con_cls);

struct MHD_Daemon* startServer(config* conf);
void stopDaemon(struct MHD_Daemon* daemon);

#endif // _WEBSERVER_H