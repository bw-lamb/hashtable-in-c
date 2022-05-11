#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hashtable.h"


#include <assert.h>


static uint64_t hash_fnv1a(const char *key);
static uint64_t linear_probe(struct hashtable *ht, uint64_t start, uint64_t end);


struct hashtable
{
    struct pair *pairs;
    uint64_t size;
    uint64_t num_elems;
};


struct hashtable *hashtable_new(uint64_t size)
{
    struct hashtable *ht = malloc(sizeof(struct hashtable));
    if(!ht)
	return NULL;

    ht->size = size;
    ht->num_elems = 0;

    ht->pairs = calloc(ht->size, sizeof(struct pair));
    if(ht->pairs == NULL)
    {
	free(ht);
	return NULL;
    }
    return ht;
}


int hashtable_insert(struct hashtable *ht, struct pair p)
{
    // NULL keys cannot be used, as key address 0 is used to determine free spaces.
    if(!p.key)
	return -1;

    int index = hash_fnv1a(p.key) % ht->size;

    // Everything is calloc'd, meaning the pointer to the key is 0.
    if(!ht->pairs[index].key)
    {
	ht->pairs[index] = p;
	return 0;
    }

    // Collision; Linear probing neccessary
    uint64_t i = linear_probe(ht, index, ht->size);
    if(i != index)
    {
	ht->pairs[i] = p;
	return 0;
    }

    i = linear_probe(ht, 0, index);
    if(i != 0)
    {
	ht->pairs[i] = p;
	return 1;
    }
    
    return 0;
}


int intern_hashtable_get_indexof(struct hashtable *ht, char *key, uint64_t *idx)
{
    for(uint64_t i = 0; i < ht->size; i++)
    {
	if(strcmp(ht->pairs[i].key, key) == 0)
	{
	    *idx = i;
	    return 0;
	}
    }
    return -1;
}


int hashtable_contains(struct hashtable *ht, char *key)
{
    for(uint64_t i = 0; i < ht->size; i++)
    {
	if(strcmp(ht->pairs[i].key, key) == 0)
	    return 1;
    }
    return 0;
}

// TODO
int hashtable_get(struct hashtable *ht, char *key)
{
    uint64_t idx = 0;
    for(uint64_t i = 0; i < ht->size; i++)
    {
	if(strcmp(ht->pairs[i].key, key) == 0)
	    return ht->pairs[i].val;
    }
    assert("hashtable_get: item not found");
}

// TODO
struct pair hashtable_get_pair(struct hashtable *ht, char *key)
{
    for(uint64_t i = 0; i < ht->size; i++)
    {
	if(strcmp(ht->pairs[i].key, key) == 0)
	    return ht->pairs[i];
    }
    assert("hashtable_get_pair: pair not found");
}


int hashtable_set(struct hashtable *ht, char *key, int val)
{
    uint64_t idx = 0;
    intern_hashtable_get_indexof(ht, key, &idx);
    ht->pairs[idx].val = val;    
    return 0;
}


void hashtable_destroy(struct hashtable *ht)
{
    for(uint64_t i = 0; i < ht->size; i++)
    {
	if(ht->pairs[i].key)
	    pair_destroy(ht->pairs[i]);
    }
    free(ht->pairs);
    free(ht);
}


// TEMP/DEBUG
void hashtable_print(struct hashtable *ht)
{
    for(int i = 0; i < ht->size; i++)
    {
	if(!ht->pairs[i].key)
	    printf("%d: empty\n", i);
	else
	    printf("%d: key: %s val: %d\n", i, ht->pairs[i].key, ht->pairs[i].val);
    }
}


static uint64_t linear_probe(struct hashtable *ht, uint64_t start, uint64_t end)
{
    for(uint64_t i = start; i < end; i++)
    {
	if(!ht->pairs[i].key)
	    return i;
    }    
    return start;
}

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL


// FNV-1a hash
static uint64_t hash_fnv1a(const char *key)
{
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++)
    {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}
