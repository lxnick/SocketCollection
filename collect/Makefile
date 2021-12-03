#
# Internetworking with TCP/IP, Volume III example code Makefile
#
#	David L Stevens, Internetworking Research Group at Purdue
#	Tue Sep 17 19:40:42 EST 1991
#

INCLUDE =

CLNTS = TCPecho TCPdaytime TCPtecho UDPecho UDPtime TCPfile
SERVS = TCPdaytimed TCPechod TCPmechod UDPtimed daytimed TCPfiled
OTHER = superd 

DEFS =
CFLAGS = -W -pedantic -ansi -g ${DEFS} ${INCLUDE}

HDR =
CSRC = TCPecho.c TCPdaytime.c TCPtecho.c UDPecho.c UDPtime.c
CXSRC = connectTCP.c connectUDP.c connectsock.c errexit.c

SSRC = TCPdaytimed.c TCPechod.c TCPmechod.c UDPtimed.c daytimed.c superd.c
SXSRC = passiveTCP.c passiveUDP.c passivesock.c sv_funcs.c

CXOBJ = connectTCP.o connectUDP.o connectsock.o errexit.o
SXOBJ = passiveTCP.o passiveUDP.o passivesock.o errexit.o

PROGS = ${CLNTS} ${SERVS} ${OTHER}

all: ${PROGS}

${CLNTS}: ${CXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${CXOBJ}

${SERVS}: ${SXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${SXOBJ}

superd: ${SXOBJ} superd.o sv_funcs.o
	${CC} -o $@ ${CFLAGS} $@.o ${SXOBJ} sv_funcs.o

clients: ${CLNTS}
servers: ${SERVS}

clean: FRC
	rm -f Makefile.bak a.out core errs lint.errs ${PROGS} *.o

depend: ${HDR} ${CSRC} ${SSRC} ${TNSRC} FRC
	maketd -a ${DEFS} ${INCLUDE} ${CSRC} ${SSRC} ${TNSRC}

install: all FRC
	@echo "Your installation instructions here."

lint: ${HDR} ${XSRC} ${CSRC} ${SSRC} FRC
	lint ${DEFS} ${INCLUDE} ${CSRC} ${SSRC} ${CXSRC} ${SXSRC}

print: Makefile ${SRC} FRC
	lpr Makefile ${CSRC} ${SSRC} ${CXSRC} ${SXSRC}

spotless: clean FRC
	rcsclean Makefile ${HDR} ${SRC}

tags: ${CSRC} ${SSRC} ${CXSRC} ${SXSRC}
	ctags ${CSRC} ${SSRC} ${CXSRC} ${SXSRC}

${HDR} ${CSRC} ${CXSRC} ${SSRC} ${SXSRC}:
	co $@

TCPecho: TCPecho.o
TCPdaytime: TCPdaytime.o
TCPtecho: TCPtecho.o
UDPecho: UDPecho.o
UDPtime: UDPtime.o
TCPdaytimed: TCPdaytimed.o
TCPechod: TCPechod.o
TCPmechod: TCPmechod.o
UDPtimed: UDPtimed.o
daytimed: daytimed.o
superd: superd.o

FRC:
	
# DO NOT DELETE THIS LINE - maketd DEPENDS ON IT
S=/usr/include/sys
I=/usr/include

TCPecho.o: $I/stdio.h TCPecho.c

TCPdaytime.o: $I/stdio.h TCPdaytime.c

TCPtecho.o: $I/sgtty.h $I/signal.h $I/stdio.h  \
	  TCPtecho.c

UDPecho.o: $I/stdio.h UDPecho.c

UDPtime.o: $I/stdio.h UDPtime.c

TCPdaytimed.o: $I/netinet/in.h $I/stdio.h  TCPdaytimed.c

TCPechod.o: $I/netinet/in.h $I/stdio.h    \
	 TCPechod.c

TCPmechod.o: $I/netinet/in.h $I/stdio.h  TCPmechod.c

UDPtimed.o: $I/netinet/in.h $I/stdio.h  UDPtimed.c

daytimed.o: $I/netinet/in.h $I/stdio.h  daytimed.c

superd.o:  $I/netinet/in.h $I/signal.h $I/stdio.h  \
	 superd.c

# *** Do not add anything here - It will go away. ***
