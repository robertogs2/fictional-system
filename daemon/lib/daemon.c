#include <daemon.h>
void initialize_daemon(){
    pid_t pid;
    
    syslog (LOG_NOTICE, "ImageServer is forking once");

    //Fork parent
    pid = fork();           
    
    //Error in forking
    if (pid < 0){           
        syslog (LOG_NOTICE, "ImageServer failed first fork");
        exit(EXIT_FAILURE); 
    }
    
    //Success in forking, exit the parent
    if (pid > 0){           
        syslog (LOG_NOTICE, "ImageServer completed first fork");
        exit(EXIT_SUCCESS); 
    }
    
    //Child becomes leader, otherwise ends the program
    if (setsid() < 0){      
        syslog (LOG_NOTICE, "ImageServer child couldn't be leader");
        exit(EXIT_FAILURE); 
    }
    
    
    // Signal handling
    syslog (LOG_NOTICE, "ImageServer handling signals");
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    
    // Set the file permissions
    umask(0);
    
    //Changes the directory to the root folder
    chdir("/"); 

    // Close all file descriptors opened
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--){
        close (x);
    }
    
    //Make logs
    syslog (LOG_NOTICE, "ImageServer completed initializing daemon");
    openlog ("ImageServer", LOG_PID, LOG_DAEMON);
}