CC=gcc
FILE= 1000-md5.txt

all: main

hashfuncs.o: hashfuncs.c hashfuncs.h
	$(CC) -c hashfuncs.c -o hashfuncs.o

bitmap.o: bitmap.c bitmap.h
	$(CC) -c bitmap.c -o bitmap.o

bloomfilter.o: bloomfilter.c bloomfilter.h
	$(CC) -c bloomfilter.c -o bloomfilter.o

vector.o: vector.c vector.h
	$(CC) -c vector.c -o vector.o

main debug: vector.o hashfuncs.o bitmap.o bloomfilter.o main.c
	$(CC) $(DEBUG) -o main main.c vector.o hashfuncs.o bitmap.o bloomfilter.o -lm

test: vector.o hashfuncs.o bitmap.o bloomfilter.o main.c
	$(CC) -o main main.c vector.o hashfuncs.o bitmap.o bloomfilter.o -lm
	./main $(FILE)

valgrind: vector.o hashfuncs.o bitmap.o bloomfilter.o main.c
	make
	valgrind ./main $(FILE)

debug: DEBUG= -DDEBUG

debug: main

clean:
	rm *.o main