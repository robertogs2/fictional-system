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
const char* path_to_config = "/tmp/config.conf";
const char* aux_file = "/tmp/config.aux";

config get_config(const char* conf_path){
    config conf;
    FILE* file = fopen(conf_path, "r"); /* should check the result */
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
    return conf;
}   

int main() {
    char buffer[256];

    // Prepare configuration struct
    config conf = get_config(path_to_config); //Read the file

    //More setup

    // log setup
    strcat(conf.dirlog, "log.txt"); 
    
    // directories setup
    strcpy(buffer, conf.dirclas);
    strcat(buffer, "red/");
    mkdir(buffer, 0777);
    
    strcpy(buffer, conf.dirclas);
    strcat(buffer, "blue/");
    mkdir(buffer, 0777);

    strcpy(buffer, conf.dirclas);
    strcat(buffer, "green/");
    mkdir(buffer, 0777);

    strcpy(buffer, conf.dirorg);
    mkdir(buffer, 0777);

    //Copies data to pointer
    config* conf_ptr = malloc(sizeof(config));
    conf_ptr->port=conf.port;
    strcpy(conf_ptr->dirlog, conf.dirlog);
    strcpy(conf_ptr->dirhist, conf.dirhist);
    strcpy(conf_ptr->dirclas, conf.dirclas);
    strcpy(conf_ptr->dirorg, conf.dirorg);

    write_file(aux_file, "");
    write_file(conf.dirlog, "Starting daemon\n");


    //skeleton_daemon();
    while (1) {
        //syslog (LOG_NOTICE, "Image server write.");
        sleep (1);


        sprintf(buffer, "Starting server at port: %d\n", conf.port);
        printf("%s", buffer);
        append_file(conf.dirlog, buffer);

        struct MHD_Daemon* daemon = startServer(conf_ptr);
        if (NULL == daemon) {
            write_file(conf.dirlog, "Failed to start daemon\n");
            //fprintf (stderr, "Failed to start daemon\n");
            return 1;
        }
        else{
            append_file(conf.dirlog, "Succeded to start daemon\n");
        }

        while(1){
            int size = read_file(aux_file);
            if(size!=0){
                stopDaemon(daemon);
                break;
            }
        }   

        sprintf(buffer, "Stopped server at port: %d\n", conf.port);
        append_file(conf.dirlog, buffer);

        break;
    }

    syslog (LOG_NOTICE, "Image server terminated.");
    closelog();

    return EXIT_SUCCESS;
}
