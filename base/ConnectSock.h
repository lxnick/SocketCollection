/* ConnectSock.h - connectsock */

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>

#ifndef	INADDR_NONE
#define	INADDR_NONE	0xffffffff
#endif	/* INADDR_NONE */

/*extern int	errno;*/

int	errexit(const char *format, ...);

/*------------------------------------------------------------------------
 * connectsock - allocate & connect a socket using TCP or UDP
 *------------------------------------------------------------------------
 */
//int 
//connectsock(const char *host, const char *service, const char *transport );

int ConnectTCP(const char * host, const char *service);

int ConnectUDP(const char * host, const char *service);

void PrintTest(char * message);
