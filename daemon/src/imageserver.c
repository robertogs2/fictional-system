/*
* daemonize.c
* This example daemonizes a process, writes a few log messages,
* sleeps 20 seconds and terminates afterwards.
* This is an answer to the stackoverflow question:
* https://stackoverflow.com/questions/17954432/creating-a-daemon-in-linux/17955149#17955149
* Fork this code: https://github.com/pasce/daemon-skeleton-linux-c
* Read about it: https://nullraum.net/how-to-create-a-daemon-in-c/
*/

#include <daemon.h>
#include <webserver.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <signal.h>
#include <pthread.h>

const char* path_to_config = "/etc/server/config.conf";
const char* aux_file = "/etc/server/config.aux";

config get_config(const char* conf_path){
    config conf;
    conf.port=-1;
    FILE* file = fopen(conf_path, "r");
    if(file==NULL){
        syslog (LOG_NOTICE, "Path to config not avaliable.");
        exit(EXIT_FAILURE); 
    }
    char line[256];
    char prev[256];
    while (fgets(line, sizeof(line), file)) {
        char* current = strtok (line, "=:");
        //prev={0};
        while (current) {
            if(!strcmp(prev,"port")){
                conf.port = atoi(current);
            }
            else if(!strcmp(prev,"dirlog")){
                strcpy(conf.dirlog, current);
                conf.dirlog[strcspn(conf.dirlog, "\n")] = 0;
            }
            else if(!strcmp(prev,"dirhist")){
                strcpy(conf.dirhist, current);
                conf.dirhist[strcspn(conf.dirhist, "\n")] = 0;
            }
            else if(!strcmp(prev,"dirclas")){
                strcpy(conf.dirclas, current);
                conf.dirclas[strcspn(conf.dirclas, "\n")] = 0;
            }
            else if(!strcmp(prev,"dirorg")){
                strcpy(conf.dirorg, current);
                conf.dirorg[strcspn(conf.dirorg, "\n")] = 0;
            }
            strcpy(prev, current);
            current = strtok (NULL, "=:");
        }
    }
    fclose(file);
    if(conf.port==-1){
        conf.port=1717;
    }
    return conf;
}   


int getSmallestName(config* conf, char* smallestFile){
    struct dirent *dp;
    DIR *dfd;
    char buffer[512];
    if ((dfd = opendir(conf->dirorg)) == NULL){
        sprintf(buffer, "Can't open %s\n", conf->dirorg);
        append_file(conf->dirlog, buffer);
        return 0;
    }

    char filename_qfd[512];
    size_t file_size = 0;

    while ((dp = readdir(dfd)) != NULL){
        struct stat stbuf ;
        sprintf( filename_qfd , "%s%s",conf->dirorg,dp->d_name) ;
        if( stat(filename_qfd,&stbuf ) == -1 ){
            sprintf(buffer, "echo Unable to stat file: %s >> /tmp/test.test", filename_qfd);
            append_file(conf->dirlog, buffer);
            continue ;
        }
        if ((stbuf.st_mode & S_IFMT) == S_IFDIR){
            continue; // Skip directories
        }
        else{
            if(stbuf.st_size > 0 && (stbuf.st_size < file_size || file_size == 0)){
                file_size = stbuf.st_size;
                sprintf(smallestFile,"%s",dp->d_name);
                return 1;
            }
            else{
                return 0;
            }
        }
    }
}

void removeSmallest(config* conf){
    char file_name[512];
    char buffer[512];
    int r = getSmallestName(conf, file_name);
    if(r){
        sprintf(buffer, "sudo rm %s%s", conf->dirorg, file_name);
        system(buffer);
    }
}

void* processImages(void* args){
    config* conf = (config*)args;
    int buffer_size=256;
    char filename[512];
    char dateBuffer[256];
    char buffer[512];
    while(1){
        
        int r = getSmallestName(conf, filename);
        if(r){
            printf("Processing %s%s\n", conf->dirorg, filename);

            getDate(dateBuffer, buffer_size);
            sprintf(buffer, "%s: Starting algorithms for file: %s\n", dateBuffer, filename);
            append_file(conf->dirlog, buffer);

            classify(conf->dirorg, filename, conf->dirclas);
            getDate(dateBuffer, buffer_size);
            sprintf(buffer, "%s: Completed classify for file: %s\n", dateBuffer, filename);
            append_file(conf->dirlog, buffer);

            histogram(conf->dirorg, filename, conf->dirhist);
            getDate(dateBuffer, buffer_size);
            sprintf(buffer, "%s: Completed histogram for file: %s\n", dateBuffer, filename);
            append_file(conf->dirlog, buffer);
            removeSmallest(conf);
        }
        sleep(1);
    }
}

int main() {
    int buffer_size=512;
    char buffer[buffer_size];
    char dateBuffer[buffer_size];

    // Prepare configuration struct
    config conf = get_config(path_to_config); //Read the file

    // More setup

    // log setup
    strcpy(buffer, conf.dirlog);
    mkdir(buffer, 0755);
    strcat(conf.dirlog, "log.txt"); 
    
    // classification directories setup
    strcpy(buffer, conf.dirclas);
    mkdir(buffer, 0755);
    strcat(buffer, "red/");
    mkdir(buffer, 0755);
    
    strcpy(buffer, conf.dirclas);
    strcat(buffer, "blue/");
    mkdir(buffer, 0755);

    strcpy(buffer, conf.dirclas);
    strcat(buffer, "green/");
    mkdir(buffer, 0755);

    // histogram directories setup
    strcpy(buffer, conf.dirhist);
    mkdir(buffer, 0755);

    // original directories setup
    strcpy(buffer, conf.dirorg);
    mkdir(buffer, 0755);

    //Copies data to pointer
    config* conf_ptr = malloc(sizeof(config));
    conf_ptr->port=conf.port;
    strcpy(conf_ptr->dirlog, conf.dirlog);
    strcpy(conf_ptr->dirhist, conf.dirhist);
    strcpy(conf_ptr->dirclas, conf.dirclas);
    strcpy(conf_ptr->dirorg, conf.dirorg);

    // Initializes files
    write_file(aux_file, "");

    getDate(dateBuffer, buffer_size);
    sprintf(buffer, "%s: %s", dateBuffer, "Starting daemon\n");
    append_file(conf.dirlog, buffer);
    syslog (LOG_NOTICE, "ImageServer service daemon is about to start.");

    initialize_daemon();

    pthread_t imageThread;
    pthread_create(&imageThread, NULL, processImages, (void*)conf_ptr);
    //pthread_join(imageThread, NULL);
    while (1) {

        
        sprintf(buffer, "Starting server at port: %d\n", conf.port);
        syslog (LOG_NOTICE, "%s", buffer);

        getDate(dateBuffer, buffer_size);
        sprintf(buffer, "%s: Starting server at port: %d\n", dateBuffer, conf.port);
        append_file(conf.dirlog, buffer);
        

        struct MHD_Daemon* daemon = startServer(conf_ptr);
        if (NULL == daemon) {
            getDate(dateBuffer, buffer_size);
            sprintf(buffer, "%s: %s", dateBuffer, "Failed to start server\n");
            append_file(conf.dirlog, buffer);
            syslog (LOG_NOTICE, "Failed to start server");
            return 1;
        }
        else{
            getDate(dateBuffer, buffer_size);
            sprintf(buffer, "%s: %s", dateBuffer, "Succeded to start server\n");
            append_file(conf.dirlog, buffer);
            syslog (LOG_NOTICE, "Succeded to start server");
        }

        while(1){
            int size = read_file(aux_file);
            if(size!=0){
                stopDaemon(daemon);
                break;
            }
        }   

        sprintf(buffer, "Stopped server at port: %d\n",  conf.port);
        syslog (LOG_NOTICE, "%s", buffer);

        getDate(dateBuffer, buffer_size);
        sprintf(buffer, "%s: Stopped server at port: %d\n", dateBuffer, conf.port);
        append_file(conf.dirlog, buffer);

        break;
    }

    getDate(dateBuffer, buffer_size);
    sprintf(buffer, "%s: Stopped daemon\n", dateBuffer);
    append_file(conf.dirlog, buffer);

    syslog (LOG_NOTICE, "ImageServer service has finished.");
    closelog();

    
    return EXIT_SUCCESS;
}
