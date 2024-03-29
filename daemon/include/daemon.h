// daemon.h

#ifndef _DAEMON_H
#define _DAEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

/*
initialize_daemon: Executes the daemon initialization process
*/

void initialize_daemon();

#endif // _DAEMON_H
