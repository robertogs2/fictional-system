sudo echo "a">>/tmp/config.aux 				#Stop the server
sudo echo >/tmp/config.aux 					#Clean
sudo systemctl restart ImageServer			#Restart the service
