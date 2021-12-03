/* FileTools.h  */

//#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


bool FileLoad(const char * filename, u_int8_t** ppbuffer, u_int32_t* plen);
