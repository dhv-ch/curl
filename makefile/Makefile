CC = gcc -Wall 

all: tr

tr: trans.o process.o upload.o dwload.o
	$(CC) trans.o process.o upload.o dwload.o -o tr -lcurl

trans.o: trans.c
	$(CC) -g -c trans.c -lcurl

process.o: process.c
	$(CC) -g -c process.c -lcurl

upload.o: upload.c
	$(CC) -g -c upload.c -lcurl

dwload.o: dwload.c
	$(CC) -g -c dwload.c -lcurl

clean:
	rm -rf *o tr 
