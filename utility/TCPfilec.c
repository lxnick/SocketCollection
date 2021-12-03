/* TCPecho.c - main, TCPecho */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <errno.h>

#include "ConnectSock.h"
#include "FileTools.h"
#include "FileXfer.h"

/*extern int	errno; */

int	TCPfilec(const char *host, const char *service, const char *filename);

#define	LINELEN		128

/*------------------------------------------------------------------------
 * main - TCP client for ECHO service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
	char	*host = "localhost";	/* host to use if none supplied	*/
	char	*service = "echo";	/* default service name		*/
	char	*filename = "filename";	/* default service name		*/

	switch (argc) {
	case 1:
		host = "localhost";
		break;
	case 3:
		service = argv[2];
		/* FALL THROUGH */
	case 2:
		host = argv[1];
		break;
	case 4:
		host = argv[1];
		service = argv[2];
		filename = argv[3];
		break;
	default:
//		fprintf(stderr, "usage: TCPecho [host [port]]\n");
		fprintf(stderr, "usage: TCPfilec host port filename\n");

		exit(1);
	}

	printf("Host %s, Port %s, File %s\r\n", host, service, filename);
	TCPfilec(host, service, filename);
	exit(0);
}

/*------------------------------------------------------------------------
 * TCPecho - send input to ECHO service on specified host and print reply
 *------------------------------------------------------------------------
 */
int
TCPfilec(const char *host, const char *service, const char * filename)
{
	char	buf[LINELEN+1];		/* buffer for one line of text	*/
	int	s, n;			/* socket descriptor, read count*/
	int	outchars, inchars;	/* characters sent and received	*/

	struct filexfer xfer;

	printf("sizeo of fileXfer %ld\r\n", sizeof(struct filexfer));	

	u_int8_t *	pbuffer = NULL;
	u_int32_t 	length = 0;

	if ( !FileLoad(filename, &pbuffer, &length))
		return 0;

	memset(&xfer, 0, sizeof(xfer));
	strcpy( xfer.filename, filename);
	strcat( xfer.filename, "det");
	xfer.prefix = htonl(FILEXFER_PREFIX);
	xfer.filelength = htonl(length);
	xfer.option = htonl(FILEXFER_OPTION);
	xfer.postfix = htonl(FILEXFER_POSTFIX);

	s = ConnectTCP(host, service);

	(void) write( s, &xfer, FILEXFER_INFO);

	u_int32_t 	send  = 0;

	while( send < length )
	{
		u_int32_t frame = length - send > 1024 ? 1024 : length;

		(void) write( s, pbuffer + send, frame);
		
		send += frame;
	}

	free( pbuffer);
	return 1;

}
