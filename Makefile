ifndef inc_flags
 inc_flags=-I/usr/local/include
endif
ifndef arc
 arc=arc64
endif
ifndef f_cpu
 f_cpu=16000000UL
endif
ifndef device
 device=atmega328p
endif
ifndef defines
 defines=-D__TMP_LIGHT
endif
all: clean
	avr-gcc -c -g -D__$(arc) $(inc_flags) $(defines) -std=c11 -DF_CPU=$(f_cpu) -Os -mmcu=$(device) -o tmp_io.o tmp_io.c
	ar rc lib/libmdl-tmp_io.a tmp_io.o
	cp *.h inc/mdl

debug: clean
	gcc -std=gnu11 -c -D__$(arc) $(inc_flags) -Wall -o tmp_io.o tmp_io.c
	gcc -std=gnu11 -D__$(arc) $(inc_flags) -Iinc -Llib -o debug debug.c tmp_io.o -lpthread -lm
clean:
	rm -f *.o *.exec debug
	rm -f inc/mdl/* lib/*
