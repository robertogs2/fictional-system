#include <daemon.h>
void initialize_daemon(){
    pid_t pid;
    
    syslog (LOG_NOTICE, "ImageServer is forking once");
    pid = fork();           //Fork parent
    
    if (pid < 0){           //Error in forking
        syslog (LOG_NOTICE, "ImageServer failed first fork");
        exit(EXIT_FAILURE); 
    }
    
    if (pid > 0){           //Success in forking, exit the parent
        syslog (LOG_NOTICE, "ImageServer completed first fork");
        exit(EXIT_SUCCESS); 
    }
    
    if (setsid() < 0){      //Child becomes leader, otherwise ends the program
        syslog (LOG_NOTICE, "ImageServer child couldn't be leader");
        exit(EXIT_FAILURE); 
    }
    
    
    // Signal handling
    syslog (LOG_NOTICE, "ImageServer handling signals");
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    
    /* Set new file permissions */
    umask(0);
    
    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");
    
    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }
    

    syslog (LOG_NOTICE, "ImageServer completed initializing daemon");
    /* Open the log file */
    openlog ("ImageServer", LOG_PID, LOG_DAEMON);
}