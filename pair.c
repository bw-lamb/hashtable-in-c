#include <stdlib.h>
#include <string.h>
#include "pair.h"


#include <assert.h>

struct pair pair_new(char *key, int val)
{
    assert(key && "key == NULL");
    size_t size = strlen(key) + 1;
    
    struct pair p;
    p.val = val;
    p.key = malloc(sizeof(char) * size);
    p.key = memmove(p.key, key, size);
   
    return p;
}

void pair_destroy(struct pair p)
{
    free(p.key);
}
