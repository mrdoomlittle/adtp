rm -f bin/*
cd ../; sh clean.sh && sh compile.sh; cd sim;
echo "DIR: $PWD"
INC=-I../inc
LIB=-L../lib
gcc -std=gnu11 $INC $LIB -Wall -o bin/switch switch.c -lmdl-tmp -lpthread
gcc -std=gnu11 $INC $LIB -Wall -o bin/node node.c -lmdl-tmp -lpthread
