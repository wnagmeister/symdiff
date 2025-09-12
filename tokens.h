#ifndef TOKENS_H

#include "symbols.h"
#define TOKENS_H

enum TOKENTYPE {OPERAND, OPERATOR};
typedef enum TOKENTYPE TOKENTYPE;

struct Token {
	TOKENTYPE token_type;
	union {
		Operand *Opd;
		Operator *Opr;
	};
};
typedef struct Token Token;

// sentinel Token value for terminating arrays of Tokens
extern Token Zero_token;

int is_zero_token (const Token *token);

// converts a string representation of ONE Operand or Operator into the
// corresponding Token
Token *tokenify (const char s[]);

// converts a space delimited string representation of a mathematical
// expression into a corresponding array of tokens, terminated with a
// Zero_token
Token *str_to_tokens (char s[]);

#endif
