#ifndef COBY_AST_H
#define COBY_AST_H

#include "types.h"
#include "list.h"
typedef struct AST_STRUCT {
    enum {
        AST_ROOT,
        AST_FUNCTION_DECLARATION,
        AST_STATEMENT_CURLY,
        AST_STATEMENT_FOR,
        AST_STATEMENT_WHILE,
        AST_STATEMENT_IF,
        AST_STATEMENT_ELIF,
        AST_STATEMENT_ELSE,
        AST_STATEMENT_SWITCH,
        AST_STATEMENT_CASE,
        AST_STATEMENT_EXPRESION,
        AST_STATEMENT_VAR_DECLARATION,
        AST_STATEMENT_CONSTANT,
        AST_STATEMENT_INJECT,
        AST_STATEMENT_EXTRACT,
        AST_STATEMENT_RETURN,
        AST_STATEMENT_ARGS,
        AST_STATEMENT_NOOP,
        AST_EXPRESSION_ARG,
        AST_EXPRESSION_IDENTIFIER,
        AST_EXPRESSION_STRING,
        AST_EXPRESSION_INTEGER,
        AST_EXPRESSION_HEX,
        AST_EXPRESSION_BIN,
        AST_EXPRESSION_FLOAT,
        AST_EXPRESSION_PARENTHESIS,
        AST_EXPRESSION_INDEX,


    } type;

    dataType dType;
    dataType lType;

    char* name;

    char* strValue;
    char charValue;
    long longValue;
    float floatValue;

    size_t listLen;
    char** strListValue;
    char* charListValue;
    long* longListValue;
    float* floatListValue;

    list_t* args;
    list_t* children;
    int id;
} AST_t;

AST_t* initAST(unsigned int type);

#endif