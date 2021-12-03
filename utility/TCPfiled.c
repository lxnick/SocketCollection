/* TCPechod.c - main, TCPechod */

#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "PassiveSock.h"
#include "FileXfer.h"
#define	QLEN		   5	/* maximum connection queue length	*/
#define	BUFSIZE		4096

extern int	errno;

void	reaper(int);
int		TCPfiled(int fd);
int		errexit(const char *format, ...);

/*------------------------------------------------------------------------
 * main - Concurrent TCP server for ECHO service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
	char	*service = "30000";	/* service name or port number	*/
	struct	sockaddr_in fsin;	/* the address of a client	*/
	int	alen;			/* length of client's address	*/
	int	msock;			/* master server socket		*/
	int	ssock;			/* slave server socket		*/

	switch (argc) {
	case	1:
		break;
	case	2:
		service = argv[1];
		break;
	default:
		errexit("usage: TCPechod [port]\n");
	}

	msock = PassiveTCP(service, QLEN);
	printf("TCP echod listen on %s\r\n", service);

	(void) signal(SIGCHLD, reaper);

	while (1) {
		alen = sizeof(fsin);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		if (ssock < 0) {
			if (errno == EINTR)
				continue;

			errexit("accept: %s\n", strerror(errno));
		}
		switch (fork()) {
		case 0:		/* child */
			printf("Child:\r\n");
			(void) close(msock);
			exit(TCPfiled(ssock));
		default:	/* parent */
			printf("Parent:\r\n");
			(void) close(ssock);
			break;
		case -1:
			printf("Fork failed\r\n");
			errexit("fork: %s\n", strerror(errno));
		}
	}
}

/*------------------------------------------------------------------------
 * TCPfiled - receive and save data to file
 *------------------------------------------------------------------------
 */
int TCPfiled(int fd)
{
	char	buf[BUFSIZ];
	int	cc;

	unsigned char info[FILEXFER_INFO];

	int headersize = read(fd, info, sizeof info);
	if ( headersize != FILEXFER_INFO)
	{
		printf("Receive header info count failed %d\r\n", headersize); 		
		errexit("echo write: %s\n", strerror(errno));
	}

	struct filexfer* xfer = (struct filexfer*) &info[0];

	if ( FILEXFER_PREFIX != ntohl(xfer->prefix))
 	{
		printf("Prefix not match %08x %08x\r\n", FILEXFER_PREFIX, ntohl(xfer->prefix) ); 		
		errexit("echo write: %s\n", strerror(errno));
	}

	FILE * pFile = fopen( xfer->filename,"w" );

    if( NULL == pFile ){
        printf( "Open File Failure %s\r\n", xfer->filename);
		errexit("echo write: %s\n", strerror(errno));
	}		


	uint32_t filesize = ntohl(xfer->filelength);

	if ( filesize > FILEXFER_MAXSIZE)
 	{
		printf("filelength too big  %08x\r\n",  filesize ); 		
		errexit("echo write: %s\n", strerror(errno));
	}

	uint8_t * buffer = malloc( filesize );
	uint32_t received = 0;

	while( received < filesize )
	{
		int frame = filesize - received > 1024 ? 1024 : filesize - received;
		int count = read(fd, buffer + received, frame);

		if ( count < 0)
		{
			errexit("echo read: %s\n", strerror(errno));
		}

		received += count;
		printf("Received %d\r\n", received);
	}

	fwrite(buffer,1, received ,pFile);
	fclose(pFile);

	return 0;
}

/*------------------------------------------------------------------------
 * reaper - clean up zombie children
 *------------------------------------------------------------------------
 */
/*ARGSUSED*/
void
reaper(int sig)
{
	int	status;

	while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0)
		/* empty */;
}
