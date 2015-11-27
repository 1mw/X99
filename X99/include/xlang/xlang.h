///
/// xlang.h
/// The xlang interpreter specifications.
///

#ifndef xlang_h
#define xlang_h

#include <types.h>

static char* xlang_operators = "+-/*";

static char* xlang_variableCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static char* xlang_separators = "+-/* ";

typedef enum
{
	VARIABLE_DECLARATION,
	VARIABLE_ASSIGNMENT,
	METHOD_DECLARATION,
	METHOD_CALL,
	TYPE,
	LITERAL_INT,
	LITERAL_BOOL,
	OPERATION,
	RETURN,
} xlang_token_type_t;

typedef enum xlang_operation_type
{
	ADDITION,
	SUBTRACTION,
	DIVISION,
	MULTIPLICATION,
}

typedef union xlang_value
{
	int integer;
	bool boolean;
} xlang_value_t;

typedef char* xlang_name_t;
typedef char* xlang_method_name_t;

typedef enum
{
	BOOL,
	INT,
} xlang_type_t;

typedef struct xlang_variable
{
	xlang_name_t name;
	xlang_value_t value;
	xlang_type_t type;
} xlang_variable_t;

typedef struct xlang_operation
{
	
}

typedef struct xlang_token
{
	xlang_token_type_t tokenType;
	
	xlang_name_t name;
	
	xlang_type_t type;
	
	xlang_value_t value;
	
	xlang_method_name_t methodName;
	
	xlang_variable_t* parameters;
	int parametersLength;
	
	xlang_value_t valueToReturn;
	xlang_type_t valueToReturnType;
	
	xlang_variable_t variableToAssign;
	xlang_value_t valueToAssign;
	xlang_type_t typeToAssign;
	
	xlang_name_t nameToDeclare;
	xlang_type_t typeToDeclare;
	xlang_value_t valueToAssignDeclare;
	xlang_type_t typeToAssignDeclare;
} xlang_token_t;

bool xlang_isOperator(char* characterInSource);
bool xlang_isType(char* characterInSource);
xlang_type_t xlang_getType(char* characterInSource);
int xlang_getNextSeparator(char* characterInSource);

int xlang_executeScript(char* source);
int xlang_test(char* src);

#endif
