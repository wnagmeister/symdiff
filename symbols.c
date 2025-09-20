#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"

void print_var (const Variable *Var) {
    putchar (Var -> repr);
}

void print_opd (const Operand *Opd, int width) {
    switch (Opd -> op_type) {
    case SCALAR:
        printf("%.*f", width - 1, Opd -> scalar);
        break;
    case VARIABLE:
		for (int i=0; i < width - 1; ++i) {
			putchar(' ');
		}
        print_var (Opd ->Var);
        break;
    }
}

void print_opr (const Operator *Opr, int width) {
    printf("%.*s", width, Opr -> repr);
}

Variable *init_var (char repr) {
	Variable *p = malloc(sizeof(*p));
	p -> repr = repr;
	return p;
}

Operand *init_scalar_opd (double scalar) {
	Operand *p = malloc(sizeof(*p));
	p -> op_type = SCALAR;
	p -> scalar = scalar;
	return p;
}

Operand *init_var_opd (Variable *Var) {
	Operand *p = malloc(sizeof(*p));
	p -> op_type = VARIABLE;
	p -> Var = Var;
	return p;
}


double add (double *args) {
    return args[0] + args[1];
};
double sub (double *args) {
    return args[0] - args[1];
};
double mul (double *args) {
    return args[0] * args[1];
};
double divd (double *args) {
    return args[0] / args[1];
};

double sq (double *args) {
    return args[0] * args[0];
};

Operator Add = {"+", 2, &add};
Operator Sub = {"-", 2, &sub};
Operator Mul = {"*", 2, &mul};
Operator Div = {"/", 2, &divd};

Operator Sq = {"sq", 1, &sq};

/* TODO: Replace NaN with (Operator) {} or something simpler, just check one
 * field perhaps? */
Operator NaN = {{'\0'}, 0, NULL};

/* TODO: Use a better data structure to store operators and variables, one that
 * does not need sentinel values, but store the array length too. I.e. a
 * dynamic array structure without needing the dynamic part (yet). Or use a 
 * hash set. */

Operator opr_lst[] = {
{"+", 2, &add},
{"-", 2, &sub},
{"*", 2, &mul},
{"/", 2, &divd},
{"sq", 1, &sq},
{{'\0'}, 0, NULL},
};

static int is_zero_opr(Operator *Opr) {
	if (Opr -> repr[0] == '\0' && Opr -> arity == 0 && Opr -> funcp == NULL)  {
		return 1;
	}
	return 0;
}

Operator *get_opr (const char str[]) {
    for (int i = 0; !is_zero_opr(&opr_lst[i]); ++i) {
        if (strcmp(str, opr_lst[i].repr) == 0) {
            return &(opr_lst[i]);
        }
    }
    return NULL;
}

Variable Zero_var = {'\0'};

Variable var_lst[10] = {{'\0'}};

// checks if there is a variable named repr in the list
int in_var_lst (char repr, const Variable list[]) {
	for (int i = 0; list[i].repr != '\0'; i++) {
		if (repr == list[i].repr) {
			return 1;
		}
	}
	return 0;
}

// adds a variable named repr to the list if not in there already
// returns the address of the variable whether it was just added or not
Variable *add_var (char repr, Variable list[]) {
	if ((get_var(repr, list))) {
		return get_var(repr, list);
	}
	int i;
	// skip non NULL variables
	for (i = 0; list[i].repr != '\0'; i++) {;}
	Variable *Var = init_var(repr);
	list[i] = *Var;
	free(Var);
	Variable V = {'\0'};
	list[i+1] = V;
	return &list[i];
}

// gets a pointer to the variabled called repr in the list if exists
// returns NULL if doesnt exist
// can be used instead of in_var_lst for checks?
Variable *get_var (char repr, Variable list[]) {
	for (int i = 0; list[i].repr != '\0'; i++) {
		if (repr == list[i].repr) {
			return &list[i];
		}
	}
	return NULL;
}

void print_var_lst (const Variable list[]) {
	for (; list -> repr != '\0'; list++) {
		print_var(list);
		putchar('\n');
	}
}

