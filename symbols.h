#ifndef SYMBOLS_H
#define SYMBOLS_H

enum OPTYPE {SCALAR, VARIABLE};
typedef enum OPTYPE OPTYPE;

struct Variable {
    char repr;
};
typedef struct Variable Variable;

struct Operand {
    enum OPTYPE op_type;
    union {
        Variable *Var;
        double scalar;
    };
};
typedef struct Operand Operand;

struct Operator {
    char repr[4];
    int arity;
    double (*funcp)(double *args);
};
typedef struct Operator Operator;

Variable *init_var (char repr);
Operand *init_scalar_opd (double scalar);
Operand *init_var_opd (Variable *Var);

// global set of implemented operators
extern Operator opr_lst[];

// gets a pointer to the Operator in opr_lst if exists, else returns NULL
Operator *get_opr (const char str[]);

// prints the given symbol to desired width
void print_opd (const Operand *Opd, int width);
void print_opr (const Operator *Opr, int width);

// global set of all variables present 
extern Variable var_lst[];

// boolean check if there is a variable named repr in the list, deprecated
// use get_var, same check and virtually the same implementation, and much
// more useful
int in_var_lst (char repr, const Variable list[]);

// adds a variable named repr to list, if not in there already
// returns a pointer to variable repr, regardless if it was just added or 
// not
Variable *add_var (char repr, Variable list[]);

// returns a pointer to a variable named repr if it is in list
// returns NULL otherwise
// use instead of in_var_lst
Variable *get_var (char repr, const Variable list[]);

void print_var_lst (const Variable list[]);

#endif
