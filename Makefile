CC=gcc

all: bf

hashfuncs.o: hashfuncs.c hashfuncs.h
	$(CC) -c hashfuncs.c -o hashfuncs.o

bitmap.o: bitmap.c bitmap.h
	$(CC) -c bitmap.c -o bitmap.o

bf: hashfuncs.o bitmap.o bf.c
	$(CC) -o bf bf.c hashfuncs.o bitmap.o

clean:
	rm *.o bf 