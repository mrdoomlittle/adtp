rm -f bin/*
cd ../; sh compile.sh; cd sim;
echo "DIR: $PWD"
INC=-I../inc
LIB=-L../lib
gcc -std=gnu11 $INC $LIB -Wall -o bin/server server.c -lmdl-tmp_io -lpthread
gcc -std=gnu11 $INC $LIB -Wall -o bin/client client.c -lmdl-tmp_io -lpthread
