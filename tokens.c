#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "tokens.h"

Token Zero_token = {.token_type=-1, .Opd = NULL};

int is_zero_token (const Token *token) {
	if (token -> token_type != OPERAND && token -> token_type != OPERATOR) {
		return 1;
	}
	if (token -> Opd == NULL && token -> Opr == NULL) {
		return 1;
	}
	return 0;
}

static int is_num (const char *s) {
	/* if s is just a single non digit char, then operator or garbage */
	if (!isdigit(*s) && *(s+1) == '\0') {
		return 0;
	}
	/* if first char is non digit and not +-, then operator or garbage */
	if (!isdigit(*s) && *s != '+' && *s != '-') {
		return 0;
	}
	/* if latter chars contain non-digits, garbage */
	while (*++s != '\0') {
		if (!isdigit(*s) && *s != '.') {
			return 0;
		}
	}
	return 1;
}

/* Do the tokens really need to be heap allocated? */
// converts a string representation to a Operand or Operator token
Token *tokenify (const char s[]) {
	
	Token *p = malloc(sizeof(*p));

	if (get_opr(s)) {
		Operator *Opr = get_opr(s);
		p -> token_type = OPERATOR;
		p -> Opr = Opr;
	} else if (is_num(s)) {
		 Operand *Opd = init_scalar_opd(atof(s));
		 p -> token_type = OPERAND;
		 p -> Opd = Opd;
	} else {		// if s is variable
		Variable *Var = add_var(*s, var_lst);
		Operand *Opd = init_var_opd(Var);
		p -> token_type = OPERAND;
		p -> Opd = Opd;
	}
	return p;
}

//converts a string expression into array of tokens
Token *str_to_tokens (char s[]) {

	int size = 4;		// token array starting size
/* TODO: Use a real dynamic array instead of the makeshift one */
	Token *array = malloc(sizeof(*array) * size); 
		
	char *str_token = strtok(s, " ");		// splits string
	// loops over the string tokens, i is the token read, the reassignment at the end is some strtok weird stuff
	int i;
	for (i = 0; str_token; ++i, str_token = strtok(NULL, " ")) {

		Token *token = tokenify(str_token);
		/* this is array[i] ? */
		*(array+i) = *token;
		free(token);


		if (i == size - 1) {
			array = realloc(array, sizeof(*array) * size * 2);
			size *= 2;
		}
	}
	array[i] = Zero_token;
	return array;

}
