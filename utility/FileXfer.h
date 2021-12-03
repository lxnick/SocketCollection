#include <sys/types.h>
#include <arpa/inet.h>

#include <assert.h>

#define RESERVED		(112)
#define FILEXFER_INFO	(128)

#define	FILEXFER_PREFIX		(0xA5A55A01)
#define	FILEXFER_OPTION		(0xABCDEF01)
#define	FILEXFER_POSTFIX	(0xFFDDEECC)

#define	FILEXFER_MAXSIZE	(64*1024*1024)


struct filexfer
{
	uint32_t	prefix;

	char filename[64];
	uint32_t	filelength;
	uint32_t	option;
	uint8_t		reserved[RESERVED];
	uint32_t	postfix;
}	__attribute__((packed));

// static_assert(sizeof(struct filexfer) == FILEXFER_INFO , "Data structure doesn't match page size");




