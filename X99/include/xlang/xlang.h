///
/// xlang.h
/// The xlang interpreter specifications.
///

#ifndef xlang_h
#define xlang_h

#include <types.h>

static char* xlang_operators = "+-/*@";

static char* xlang_variableCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static char* xlang_separators = "+-/*@ ";

typedef enum
{
	VARIABLE_NAME,
	METHOD_NAME,
	TYPE,
	LITERAL_INT,
	LITERAL_BOOL,
	OPERATOR_ADDITION,
	OPERATOR_SUBTRACTION,
	OPERATOR_DIVISION,
	OPERATOR_MULTIPLICATION,
	OPERATOR_RETURN,
} xlang_token_type_t;

typedef union xlang_value
{
	int integer;
	bool boolean;
} xlang_value_t;

typedef char* xlang_name_t;

typedef enum
{
	BOOL,
	INT,
} xlang_type_t;

typedef struct xlang_token
{
	xlang_name_t name;
	xlang_token_type_t type;
	xlang_value_t value;
} xlang_token_t;

bool xlang_isOperator(char* characterInSource);
bool xlang_isType(char* characterInSource);
xlang_type_t xlang_getType(char* characterInSource);
int xlang_getNextSeparator(char* characterInSource);

int xlang_executeScript(char* source);
int xlang_test(char* src);

#endif
