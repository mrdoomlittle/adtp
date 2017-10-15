gcc -c -std=gnu11 -o tmp_io.o tmp_io.c
ar rc lib/libmdl-tmp_io.a tmp_io.o
cp tmp_io.h inc/mdl
