LIBNAME = libimageserver
SRCS = webserver.c daemon.c
LIB =  $(LIBNAME).a
OBJS =  $(SRCS:.c=.o)
AR = ar rvs
INCLUDE_DIR = ../include/
CC = gcc
CFLAGS = -c -I$(INCLUDE_DIR) #-lmicrohttpd

clean: $(LIB)
		rm $(OBJS)

$(LIB) : $(OBJS)
		$(AR) $(LIB) $(OBJS)

$(OBJS) : $(SRCS)
		$(CC) $(CFLAGS) $(SRCS)

