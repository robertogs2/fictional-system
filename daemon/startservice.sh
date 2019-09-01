#!/bin/bash
sudo cp bin/imageserver /usr/bin/ImageServer   						#copy the executable to usr/bin
sudo cp ImageServer.service /lib/systemd/system/ImageServer.service #copy service to the systemd folder
sudo systemctl daemon-reload										#reload the systemd service
#sudo systemctl enable ImageServer 									#use this to enable it for boot
sudo systemctl start ImageServer									#start the service