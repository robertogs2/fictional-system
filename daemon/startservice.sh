#!/bin/bash
echo "Removing previous"
sudo rm /usr/bin/ImageServer
sudo rm /lib/systemd/system/ImageServer.service
echo "Copying new binary"
sudo cp bin/imageserver /usr/bin/ImageServer 						#copy the executable to usr/bin
echo "Copying new service"  						
sudo cp ImageServer.service /lib/systemd/system/ImageServer.service #copy service to the systemd folder
echo "Reload daemon services"  
sudo systemctl daemon-reload										#reload the systemd service
echo "Start daemon"  
sudo systemctl start ImageServer									#start the service