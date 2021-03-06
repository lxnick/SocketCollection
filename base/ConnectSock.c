/* connectsock.c - connectsock */

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

#include <errno.h>


#include "ConnectSock.h"

#ifndef	INADDR_NONE
#define	INADDR_NONE	0xffffffff
#endif	/* INADDR_NONE */

/*extern int	errno;*/

int	errexit(const char *format, ...);

int ConnectSock(const char *host, const char *service, const char *transport );

/*------------------------------------------------------------------------
 * connectsock - allocate & connect a socket using TCP or UDP
 *------------------------------------------------------------------------
 */
int
ConnectSock(const char *host, const char *service, const char *transport )
/*
 * Arguments:
 *      host      - name of host to which connection is desired
 *      service   - service associated with the desired port
 *      transport - name of transport protocol to use ("tcp" or "udp")
 */
{
	struct hostent	*phe;	/* pointer to host information entry	*/
	struct servent	*pse;	/* pointer to service information entry	*/
	struct protoent *ppe;	/* pointer to protocol information entry*/
	struct sockaddr_in sin;	/* an Internet endpoint address		*/
	int	s, type;	/* socket descriptor and socket type	*/


	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;

    /* Map service name to port number */
	if ( pse = getservbyname(service, transport) )
		sin.sin_port = pse->s_port;
	else if ( (sin.sin_port = htons((uint16_t)atoi(service))) == 0 )
		errexit("can't get \"%s\" service entry\n", service);

    /* Map host name to IP address, allowing for dotted decimal */
	if ( phe = gethostbyname(host) )
/*	memcpy(&sin.sin_addr, phe->h_addr, phe->h_length); */
		memcpy(&sin.sin_addr, phe->h_addr_list[0], phe->h_length);
	else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE )
		errexit("can't get \"%s\" host entry\n", host);

    /* Map transport protocol name to protocol number */
	if ( (ppe = getprotobyname(transport)) == 0)
		errexit("can't get \"%s\" protocol entry\n", transport);

    /* Use protocol to choose a socket type */
	if (strcmp(transport, "udp") == 0)
		type = SOCK_DGRAM;
	else
		type = SOCK_STREAM;

    /* Allocate a socket */
	s = socket(PF_INET, type, ppe->p_proto);
	if (s < 0)
		errexit("can't create socket: %s\n", strerror(errno));

    /* Connect the socket */
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errexit("can't connect to %s.%s: %s\n", host, service,
			strerror(errno));
	return s;
}


/*------------------------------------------------------------------------
 * connectTCP - connect to a specified TCP service on a specified host
 *------------------------------------------------------------------------
 */
int
ConnectTCP(const char *host, const char *service )
/*
 * Arguments:
 *      host    - name of host to which connection is desired
 *      service - service associated with the desired port
 */
{
    return ConnectSock( host, service, "tcp");
}


/*------------------------------------------------------------------------
 * connectUDP - connect to a specified UDP service on a specified host
 *------------------------------------------------------------------------
 */
int
ConnectUDP(const char *host, const char *service )
/*
 * Arguments:
 *      host    - name of host to which connection is desired
 *      service - service associated with the desired port
 */
{
    return ConnectSock(host, service, "udp");
}
void PrintTest(char* message)
{

	printf("Hello %s\r\n", message);
}
