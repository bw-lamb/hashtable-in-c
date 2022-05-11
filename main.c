#include <stdio.h>
#include <string.h>
#include "hashtable.h"

int main(void)
{
    HashTable *ht = hashtable_new(C_HT_MAX_SIZE);

    char *foo[] =
    {
	"a", "b", "c", "d",
	"e", "f", "g", "h",
	"i", "j", "k", "l",
	"m", "n", "o", "p"
    };
    
    struct pair bar[16];
    for(int i = 0; i < 16; i++)
    {
	bar[i] = pair_new(foo[i], i);
	hashtable_insert(ht, bar[i]);
    }

    hashtable_set(ht, "a", 66666);
    hashtable_print(ht);


    printf("contains \"a\"?: %d\n", hashtable_contains(ht, "a"));
    printf("contains \"z\"?: %d\n", hashtable_contains(ht, "z"));
    printf("\"j\": %d\n", hashtable_get(ht, "j"));
    
    hashtable_destroy(ht);
    
    return 0;
}
