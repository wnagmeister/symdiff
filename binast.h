#ifndef BINAST_H

#include "bintree.h"
#include "tokens.h"

#define BINAST_H

void print_value (int, void *, int);
Bnode *astify_rpn (Token []);
Bnode *astify (char []);
Bnode *astifyf (char str[], Bnode *subs[]);

#endif
