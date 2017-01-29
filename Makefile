all:
	avr-gcc -c -g -std=c11 -DF_CPU=16000000UL -Os -mmcu=atmega328p -o io.o io.c
	gcc -c -std=c11 -o io_.o io.c
	gcc -std=c11 -o main main.c io_.o
	#ar rcs libtmp_io.a io.o
	#g++ -std=c++11 -L. -o main main.cpp -ltmp_io
clean:
	rm -f *.o
