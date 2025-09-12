#ifndef TREE_H

#define TREE_H

struct Tnode {
    int value_type;
    void *value;
    void *childn[];
};
typedef struct Tnode Tnode;

Tnode *init_tnode (int, void *, int, void * []);
Tnode *tnodify (int, void *);
void fini_tnode (Tnode *tnode);
int no_childn (const Tnode *);
int is_leaf (const Tnode *);
void print_tree (const Tnode *, int, int);
void print_value (int, const void *, int);
void pt (const Tnode *);

#endif
