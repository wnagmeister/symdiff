#ifndef BINTREE_H

#define BINTREE_H

#define PRINTWIDTH 5

struct Bnode {
    int value_type;
    void *value;
    void *childn[2];
};
typedef struct Bnode Bnode;

Bnode *init_bnode (int, void *, void *[2]);
Bnode *bnodify (int, void *);
int is_leaf (Bnode *);
void print_btree (Bnode *, int, int);
void print_value (int, void *, int);
void pbt (Bnode *);

#endif
