gcc -o ImageServer daemonize.c 					#compiled the server/daemon code
sudo cp ImageServer /usr/bin/ 					#copy the executable to usr/bin

sudo cp ImageServer.service /lib/systemd/system #copy service to the systemd folder
sudo systemctl daemon-reload 					#reload the systemd service
#sudo systemctl enable ImageServer 				#use this to enable it for boot
sudo systemctl start ImageServer				#start the service