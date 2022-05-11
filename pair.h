#ifndef C_PAIR_h
#define C_PAIR_h

struct pair
{
    char *key;
    int val;
};

struct pair pair_new(char *key, int val);
void pair_destroy(struct pair p);


#endif /* C_PAIR_h */
