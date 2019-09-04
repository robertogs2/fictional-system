SRC_DIR=src/
LIB_DIR=lib/

all:
	make -C $(LIB_DIR)
	make -C $(SRC_DIR)

install:
	sudo rm -rf /usr/bin/imageserver 									#Remove previous binary
	sudo rm -rf /lib/systemd/system/ImageServer.service					#Remove previous service
	sudo cp bin/imageserver /usr/bin/ImageServer 	 					#Copy the executable to usr/bin								
	sudo cp ImageServer.service /lib/systemd/system/ImageServer.service #Copy service to the systemd folder	
	sudo systemctl daemon-reload	 									#Reload the systemd service		

	sudo mkdir -p /etc/server/
	sudo rm -rf /etc/server/config.conf
	sudo rm -rf /etc/server/config.aux
	sudo cp config.conf /etc/server/config.conf
	sudo cp config.conf /etc/server/config.aux
	sudo chmod 777 /etc/server/config.conf
	sudo chmod 777 /etc/server/config.aux
	sudo echo >/etc/server/config.aux			