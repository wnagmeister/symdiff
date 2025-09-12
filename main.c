#include "ast.h"
#include "tree.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>

int main (void) {
	char sst[] = "x y + 1 2 * + 3 4 / q w - + *";

	Tnode *t = astify(sst);
	pt(t);
	free(t);



	
	
	return 0;
}
