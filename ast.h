#ifndef AST_H

#include "tree.h"
#include "tokens.h"

#define AST_H

void print_value (int, const void *, int);
Tnode *astify_rpn (Token []);
Tnode *astify (char []);
Tnode *astifyf (char str[], Tnode *subs[]);

#endif
