#
# Internetworking with TCP/IP, Volume III example code Makefile
#
#	David L Stevens, Internetworking Research Group at Purdue
#	Tue Sep 17 19:40:42 EST 1991
#


CFLAGS = -I../base -W
LFLAGS = -L../base -lmibase
BINARY = ../bin/

PROGRAM = TCPechoc TCPechod

all: ${PROGRAM}

%.o:%.c
	${CC} -o $@  ${CFLAGS} ${LFLAGS} 

#TCPecho: TCPecho.c 
#	${CC} -o $@ $<  ${CFLAGS} ${LFLAGS}

TCPechoc: TCPechoc.c 
	${CC} -o ${BINARY}$@ $<  ${CFLAGS} ${LFLAGS}

TCPechod: TCPechod.c 
	${CC} -o ${BINARY}$@ $<  ${CFLAGS} ${LFLAGS}

clean:
	rm -f ${PROGRAM}  *.o

# *** Do not add anything here - It will go away. ***



