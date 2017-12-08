sh clean.sh
gcc -c -std=gnu11 -o tmp_io.o tmp_io.c
gcc -c -std=gnu11 -o forward.o forward.c
ar rc lib/libmdl-tmp.a tmp_io.o forward.o
cp *.h inc/mdl
