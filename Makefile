CXXFLAGS=-I/usr/local/include -D__DEBUG_ENABLED
ARC=-DARC32
debug: clean
	gcc -std=c11 -c $(ARC) $(CXXFLAGS) -Wall -o tmp_io.o tmp_io.c
	gcc -std=c11 $(ARC) $(CXXFLAGS) -Iinc -Llib -o debug debug.c tmp_io.o -lpthread
clean:
	rm -f *.o *.exec debug
