#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Tnode *init_tnode (int value_type, void *value, int no_childn, void *childn[]) {
	// allocates for one more element in the childn array for a null terminator
	Tnode *p = malloc(sizeof(*p) + (no_childn + 1) * sizeof(void *));
    p -> value_type = value_type;
    p -> value = value;
	for (int i = 0; i < no_childn; i++) {
		p -> childn[i] = childn[i];
	}
	p -> childn [no_childn] = NULL;
	return p;
}

Tnode *tnodify (int value_type, void *value) {
	return init_tnode(value_type, value, 0, NULL);
}
// work in this
void fini_tnode (Tnode *tnode) {
	free (tnode);
}

int no_childn (const Tnode *tnode) {
	int n;
	for (n = 0; tnode -> childn[n]; ++n) {};
	return n;
}

int is_leaf (const Tnode *tnode) {
	return (no_childn (tnode) == 0) ? 1 : 0;
}

static void rjust(int width, char c) {
    for (int i = 0; i < width; i++) {
        putchar(c);
    }
}

static void branch_lines (int width, int indent) {
	rjust (indent - width, ' ');
	if (indent >= width) {
		putchar ('|');
		rjust(width - 1, '-');
	}
}

void print_tree (const Tnode *tnode, int width, int indent) {
	putchar('\n');
	int n = no_childn (tnode);
	if (n == 0) {
		branch_lines(width, indent);
        print_value (tnode -> value_type, tnode -> value, width);
	} else {
		// multiple childn
		int mid = n / 2;
		while (n--) {
			print_tree(tnode -> childn [n], width, indent + width);
			if (n == mid) {
				branch_lines(width, indent);
				print_value (tnode -> value_type, tnode -> value, width);
			}	
		}
	}
	putchar('\n');
}

void pt (const Tnode *tnode) {
	print_tree(tnode, 5, 0);
}

