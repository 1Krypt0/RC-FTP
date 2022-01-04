##
# RC-FTP
#
# @file
# @version 0.1

CC = gcc
CFLAGS = -c -Wall

all: download.o communication.o connection.o file.o parser.o
	$(CC) download.o communication.o connection.o file.o parser.o -o download

download.o: download.c
	$(CC) $(CFLAGS) download.c -o download.o

communication.o: communication.c
	$(CC) $(CFLAGS) communication.c -o communication.o

connection.o: connection.c
	$(CC) $(CFLAGS) connection.c -o connection.o

file.o: file.c
	$(CC) $(CFLAGS) file.c -o file.o

parser.o: parser.c
	$(CC) $(CFLAGS) parser.c -o parser.o

clean: # -rm -f *.o recv write
	-rm -f *.o download


# end
