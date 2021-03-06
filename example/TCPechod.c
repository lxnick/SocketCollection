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

#define	QLEN		   5	/* maximum connection queue length	*/
#define	BUFSIZE		4096

extern int	errno;

void	reaper(int);
int	TCPechod(int fd);
int	errexit(const char *format, ...);
//int	passiveTCP(const char *service, int qlen);

/*------------------------------------------------------------------------
 * main - Concurrent TCP server for ECHO service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
	char	*service = "echo";	/* service name or port number	*/
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

			exit(TCPechod(ssock));
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
 * TCPechod - echo data until end of file
 *------------------------------------------------------------------------
 */
int
TCPechod(int fd)
{
	char	buf[BUFSIZ];
	int	cc;

	while (cc = read(fd, buf, sizeof buf)) {
		printf("Receive count %d\r\n", cc); 		
		if (cc < 0)
			errexit("echo read: %s\n", strerror(errno));
		if (write(fd, buf, cc) < 0)
			errexit("echo write: %s\n", strerror(errno));
	}
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
