#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"


Bnode *init_bnode (int value_type, void *value, void *childn[2]) {
    Bnode *p = malloc(sizeof(*p));
    p -> value_type = value_type;
    p -> value = value;
    p -> childn[0] = childn[0];
    p -> childn[1] = childn[1];
    return p;
}

Bnode *bnodify (int value_type, void *value) {
	void *childn[] = {NULL, NULL};
    return init_bnode (value_type, value, childn);
}

int is_leaf (Bnode *bnode) {
    if (bnode -> childn [0] == NULL && bnode -> childn [1] == NULL) {
        return 1;
    }
    return 0;
}

static void rjust(int width, char c) {
    for (int i = 0; i < width; i++) {
        putchar(c);
    }
}

static void branch_lines (int width, int indent) {
	rjust (indent - width, ' ');
	
	(indent >= width) ? putchar('|'), rjust (width-1, '-') : 1 ;
}

void print_btree (Bnode *bnode, int width, int indent) {
	putchar('\n');
    if (is_leaf (bnode)) {
		branch_lines(width, indent);
        print_value (bnode -> value_type, bnode -> value, width);
    } else {
        print_btree (bnode -> childn[0], width, indent + width);

		branch_lines(width, indent);
        print_value (bnode -> value_type, bnode -> value, width);

        print_btree (bnode -> childn[1], width, indent + width);
    }
	putchar('\n');
}

void pbt (Bnode *bnode) {
	print_btree(bnode, 5, 0);
}
