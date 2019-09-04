sudo echo "a">>/tmp/config.aux 				#Stop the daemon
sudo systemctl stop ImageServer				#Stop the service	
sudo echo >/tmp/config.aux 					#Clean