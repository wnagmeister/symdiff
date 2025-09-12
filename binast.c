#include <stdio.h>
#include <stdlib.h>
#include "symbols.h"
#include "bintree.h"
#include "tokens.h"
#include "binast.h"

void print_value (int value_type, void *value, int width) {
	switch (value_type) {
		case OPERAND:
			print_opd(value, width);
			break;
		case OPERATOR:
			print_opr(value, width);
			break;
	}
}

struct Stack {
	int max;		// max stack size and next free stack position
	int sp;
	void *array[];
};

static int push (void *value, struct Stack *stack) {
	if (stack -> sp < stack -> max) {
		stack ->array [stack -> sp++] = value;
		return 0;
	}
	return -1;
}

static void *pop (struct Stack *stack) {
	if (stack -> sp > 0) {
		return stack -> array [--stack -> sp];
	}
	return NULL;
}

static struct Stack *init_stack (int max) {
	struct Stack *p = malloc(sizeof(*p) + sizeof(void*[max]));
	p -> max = max;
	p -> sp = 0;
	return p;
}

// memory leak maybe if some operand/operator never gets popped
// address never gets onto the tree, and is lost when the stack its 
// located on is freed
Bnode *astify_rpn (Token tokens[]) {

	struct Stack *stack = init_stack (4);

	Token *token = tokens;		// copies pointer for incrementing
								// preserves original for freeing

	while (!is_zero_token(token)) {
		if (token -> token_type == OPERAND) {
			push(bnodify(OPERAND, token -> Opd), stack);
		} else {
			// token -> token_type == OPERATOR
			Bnode *childn[2] = {pop(stack), pop(stack)};
			push(init_bnode(OPERATOR, token -> Opr, (void *)childn), stack);
		}
		token++;
	}
	free(tokens);
	Bnode *p = pop(stack);
	free(stack);
	return p;
}

Bnode *astifyf_rpn (Token tokens[], char c, Bnode *subs[]) {

	struct Stack *stack = init_stack (4);

	Token *token = tokens;		// copies pointer for incrementing
								// preserves original for freeing

	while (!is_zero_token(token)) {
		if (token -> token_type == OPERAND) {
			if (token -> Opd -> op_type == VARIABLE && token -> Opd -> Var -> repr ==  c) {
				// token is a placeholder
				push (*subs++, stack);
			} else { 
			push(bnodify(OPERAND, token -> Opd), stack);
			}	
		} else {
			// token -> token_type == OPERATOR
			/* int arity = token -> Opr ->arity; */
			/* struct Stack *childn = init_stack(arity); */
			/* while (arity--) { */
			/* 	push (pop(stack), childn); */
			/* } */
			Bnode *childn[2] = {pop(stack), pop(stack)};
			push(init_bnode(OPERATOR, token -> Opr, (void *)childn), stack);
		}
		token++;
	}
	free(tokens);
	Bnode *p = pop(stack);
	free(stack);
	return p;
}

Bnode *astify (char str[]) {
	return astify_rpn(str_to_tokens(str));
}

Bnode *astifyf (char str[], Bnode *subs[]) {
	return astifyf_rpn(str_to_tokens(str), '@', subs);
}


// evaluates the tree, all variables set to x
