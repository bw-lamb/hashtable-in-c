#ifndef C_HASHTABLE_h
#define C_HASHTABLE_h

#include <stdlib.h>
#include "pair.h"

// TODO: Make this UINT64_T_MAX once structure is stable?
#define C_HT_MAX_SIZE 16

typedef struct hashtable HashTable;

HashTable *hashtable_new(size_t size);
int hashtable_insert(HashTable *ht, struct pair p);
int hashtable_contains(HashTable *ht, char *key);
int hashtable_get(struct hashtable *ht, char *key);
struct pair hashtable_get_pair(HashTable *ht, char *key);
int hashtable_set(HashTable *ht, char *key, int val);
void hashtable_destroy(HashTable *ht);

//TEMP/DEBUG
void hashtable_print(struct hashtable *ht);

#endif /* C_HASHTABLE_h */
