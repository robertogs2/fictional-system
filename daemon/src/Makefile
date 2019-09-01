CC=gcc
DAEMON=imageserver
BIN_DIR = ../bin/
INC_DIR = ../include/
LIB = ../lib/libimageserver.a
LDFLAGS = `pkg-config --cflags --libs MagickWand` -lm -lmicrohttpd 

$(DAEMON):
	$(CC) -o $(BIN_DIR)$(DAEMON) $(DAEMON).c $(LIB) -I $(INC_DIR) $(LDFLAGS)
