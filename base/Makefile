#
# Internetworking with TCP/IP, Volume III example code Makefile
#
#	David L Stevens, Internetworking Research Group at Purdue
#	Tue Sep 17 19:40:42 EST 1991
#

SUBDIRS = base example

all: libs

libmibase.a: ConnectSock.o PassiveSock.o ErrorExit.o FileTools.o
	ar rcs $@ $+ 
	ranlib $@

ConnectSock.o: ConnectSock.c
	gcc -O -c ConnectSock.c

PassiveSock.o: PassiveSock.c
	gcc -O -c PassiveSock.c

FileTools.o: FileTools.c
	gcc -O -c FileTools.c

errexit.o: ErrorExit.c
	gcc -O -c ErrorExit.c

libs: libmibase.a
 
clean:
	rm -f libmibase.a *.o 

# *** Do not add anything here - It will go away. ***
