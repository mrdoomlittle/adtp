CXXFLAGS=-I/usr/local/include
ARC=-DARC32
all: clean
	avr-gcc -c -g $(ARC) $(CXXFLAGS) -std=c11 -DF_CPU=16000000UL -Os -mmcu=atmega328p -o tmp_io.o tmp_io.c
	ar rc lib/libtmp_io.a tmp_io.o
	cp tmp_io.h inc

debug: clean
	gcc -std=c11 -c $(ARC) $(CXXFLAGS) -Wall -o tmp_io.o tmp_io.c
	gcc -std=c11 $(ARC) $(CXXFLAGS) -Iinc -Llib -o debug debug.c tmp_io.o -lpthread
clean:
	rm -f *.o *.exec debug
	rm -f inc/* lib/*
