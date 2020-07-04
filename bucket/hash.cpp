// hash.cpp
#include "hash.h"
#include <string.h>

int Hash (char* key)
{
	int sum = 0;
	int len = strlen(key);
	if (len % 2 == 1) len ++; // make len even
	// for an odd length string, use the trailing '\0' as part of key
	for (int j = 0; j < len; j += 2)
		sum = (sum + 100 * key[j] + key[j+1]) % 19937;
	return sum;
}

int MakeAddress (char * key, int depth)
{
	int retval = 0;
	int mask = 1;
	int hashVal = Hash(key);

	for (int j = 0; j < depth; j++)
	{
		retval = retval << 1;
		int lowbit = hashVal & mask;
		retval = retval | lowbit;
		hashVal = hashVal >> 1;
	}
	return retval;
}

