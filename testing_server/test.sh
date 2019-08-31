sudo apt install libmicrohttpd-dev
gcc -o simplepost simplepost.c -I . -lmicrohttpd
./simplepost