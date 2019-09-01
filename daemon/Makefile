SRC_DIR=src/
BIN_DIR=bin/
LIB_DIR=lib/

SERVER=ImageServer
SERVICE=$(SERVER).service
DAEMON=imageserver

USR_BIN_PATH = /usr/bin/
SYS_PATH = /lib/systemd/system/

SYSCTL=systemctl

all: $(DAEMON)
	sudo cp $(BIN_DIR)$(DAEMON) $(USR_BIN_PATH)$(SERVER)  	#copy binary
	sudo cp $(SERVICE) $(SYS_PATH)$(SERVICE) 				#copy service
	sudo $(SYSCTL) daemon-reload							#reload the systemd service
	sudo $(SYSCTL) start $(SERVER)							#start the service

$(DAEMON):
	make -C $(LIB_DIR)
	#make -C $(SRC_DIR)