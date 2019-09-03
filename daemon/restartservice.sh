sudo echo "a">>/tmp/config.aux 
#sudo systemctl stop ImageServer				#stop the service
sudo systemctl restart ImageServer			#start the service
sudo echo >/tmp/config.aux 
