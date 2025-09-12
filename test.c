#include <stdio.h>
#include "void_darray.h"

struct Foo {
	int x;
	char y;
};
typedef struct Foo Foo;

void print_value (void *F) {
	Foo *G = (Foo *) F;
	printf("%d\t%c\n", G -> x, G -> y);
}

int main (void) {
	Foo f1 = {10, 'a'};
	Foo f2 = {20, 'b'};
	/* Stack *S = init(10); */

	/* push(&f1, S); */
	/* push(&f2, S); */
	/* printf("%d", size(S)); */
	/* Foo *f3 = pop(S); */
	/* print_foo(f3); */
	/* f3 = pop(S); */
	/* print_foo(f3); */
	/* printf("%d", size(S)); */

	Set *S = init(10);
	printf("%d", size(S));
	add(&f1, S);
	printf("%d", size(S));
	add(&f2, S);
	printf("%d", size(S));
	add(&f1, S);
	printf("%d\n\n", size(S));
	print_darray(S);
	del(&f1, S);
	print_darray(S);


	return 0;
}
