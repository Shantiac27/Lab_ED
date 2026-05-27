
#include <HashQ.h>

int fn_hashQ(HashQTable hashtable, int key)
{
	
}

int fn_rehashQ(HashQTable hashtable, int index, int k)
{
	return (index+k*k) % hashtable.len;
}

int fn_insertKey(HashQTable *hashtable, void *data)
{
	int index, n_index, k, key;
}