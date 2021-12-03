/* FileTools.h  */
#include "FileTools.h"

#include <sys/stat.h>
#include <stdio.h>


bool FileLoad(const char * filename, u_int8_t** ppbuffer, u_int32_t* plen)
{
	struct stat st;

	if ( stat(filename, &st))
	{
		printf("stat %s failed\r\n", filename);
		return false;
	}

	*plen = st.st_size;

	if ( *plen <= 0 )
	{
		printf("zero file %s\r\n", filename);
		return false;
	}

	*ppbuffer = malloc( *plen);
	if ( *ppbuffer == NULL)
	{
		printf("allocate failed %s\r\n", filename);
		return false;
	}

	FILE* pFile = fopen(filename, "r");
	if ( pFile == NULL)
	{
		printf("ope file  failed %s\r\n", filename);
		return false;
	}

	int count = fread(*ppbuffer, 1, *plen, pFile);
	if ( count != *plen )
	{
		printf("read %d but get %d \r\n", *plen, count);
	}

	fclose(pFile);

	return true;
}
