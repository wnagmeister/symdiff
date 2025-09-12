#include <stdio.h>
#include <stdlib.h>
#include "symbols.h"
#include "tree.h"
#include "tokens.h"
#include "ast.h"

#define USE_STACK

#include "void_darray.h"

void print_value (int value_type, const void *value, int width) {
	switch (value_type) {
		case OPERAND:
			print_opd(value, width);
			break;
		case OPERATOR:
			print_opr(value, width);
			break;
	}
}

/* struct Stack { */
/* 	int max;		// max stack size */
/* 	int sp;			// next free stack position */
/* 	void *array[]; */
/* }; */

/* struct Stack *init_stack (int max) { */
/* 	struct Stack *p = malloc(sizeof(*p) + sizeof(void*[max])); */
/* 	p -> max = max; */
/* 	p -> sp = 0; */
/* 	return p; */
/* }; */

/* struct Stack *resize_stack (int new_max, struct Stack *stack) { */
/* 	if (new_max < stack -> max) { */
/* 		return stack; */
/* 	} else { */
/* 	struct Stack *p = realloc(stack, sizeof(*p) + sizeof(void*[new_max])); */
/* 	p -> max = new_max; */
/* 	return p; */
/* 	} */
/* } */

/* void print_stack (const struct Stack *stack, char c) { */
/* 	putchar(c); */
/* 	printf("MAX: %d\t\tSP: %d\n", stack -> max, stack -> sp); */
/* 	for (int i = 0; i < stack -> sp; ++i) { */
/* 		print_value(OPERAND, ((Tnode *)(stack -> array [i])) -> value, 2); */
/* 		putchar (' '); */
/* 	} */
/* 	putchar('\n'); */
/* } */

/* int push (void *value, struct Stack *stack) { */
/* 	if (stack -> sp < stack -> max) { */
/* 	stack -> array [stack -> sp++] = value; */
/* 	return 0; */
/* 	} else { */
/* 		return -1; */
/* 	} */ 
/* } */

/* struct Stack *smart_push (void *value, struct Stack *stack) { */
/* 	if (stack -> sp >= stack -> max) { */
/* 		stack = resize_stack(stack -> max * 2, stack); */
/* 	} */
/* 	stack -> array [stack -> sp++] = value; */
/* 	return stack; */
/* } */

/* void *pop (struct Stack *stack) { */
/* 	if (stack -> sp > 0) { */
/* 		// stack -> array is a pointer to the first void pointer in an */
/* 		// array of void pointers */
/* 		// stack -> array [m] is the void pointer in the mth position */
/* 		// of the aforementioned array of void pointers */
/* 		return stack -> array [--stack -> sp]; */
/* 	} */
/* 	return NULL; */
/* } */

/* // retrieves the pointer to the nth element from the top of the stack */
/* // in essence retrieves the last n elements of the stack */
/* // does not remove those elements from the stack */
/* void **peekn (int n, struct Stack *stack) { */
/* 	// stack -> array is a pointer to the first void pointer in an */
/* 	// array of void pointers */
/* 	// stack -> array + m is a pointer to the mth void pointer in an */
/* 	// array of void pointers */
/* 	return (stack -> array) + (stack -> sp - n); */
/* } */

// converts a list of tokens in reverse polish notation to an AST
Tnode *tokens_to_ast (Token tokens[], char c, Tnode *subs[]) {
	// memory leak maybe if some operand/operator never gets popped
	// address never gets onto the tree, and is lost when the stack
	// its located on is freed
	/* struct Stack *stack = init_stack (4); */
	Stack *stack = init(4);

	Token *token = tokens;		// copies pointer for incrementing
								// preserves original for freeing

	while (!is_zero_token(token)) {
		if (token -> token_type == OPERAND) {
			if (token -> Opd -> op_type == VARIABLE && token -> Opd -> Var -> repr ==  c) {
				// if token is a placeholder
				push (*subs++, stack);
			} else { 
				/* stack = resize_stack(stack -> max * 2, stack); */
				push(tnodify(OPERAND, token -> Opd), stack);
			}	
		} else {
			int arity = token -> Opr -> arity;
			/* Tnode *new_tnode = init_tnode(OPERATOR, token -> Opr, arity, peekn(arity, stack)); */
			Tnode *new_tnode = init_tnode(OPERATOR, token -> Opr, arity, (stack -> data)+(size(stack) - arity));
			while (arity--) {popp(stack);};
			push(new_tnode, stack);
		}
		token++;
	}
	free(tokens);
	Tnode *p = popp(stack);
	/* free(stack); */
	destroy(stack);
	return p;
}

Tnode *astify (char str[]) {
	return tokens_to_ast(str_to_tokens(str), '\0', NULL);
}

// astify formatted
// converts str into an AST, replacing all @ variables with the
// substitution nodes given, in the order in str
Tnode *astifyf (char str[], Tnode *subs[]) {
	return tokens_to_ast(str_to_tokens(str), '@', subs);
}

