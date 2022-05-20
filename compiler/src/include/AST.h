#ifndef COBY_AST_H
#define COBY_AST_H

#include "main.h"
#include "types.h"
#include "list.h"
#include "stackFrame.h"

struct VISITOR_STRUCT;

typedef struct AST_STRUCT {
    enum {
        AST_COMPOUND,
        AST_FUNCTION,
        AST_CALL,
        AST_ASSIGNMENT = 99,
        AST_DEFINITION_TYPE,
        AST_VARIABLE,
        AST_STATEMENT_RETURN,
        AST_STATEMENT_IF,
        AST_STATEMENT_ELSE_IF,
        AST_STATEMENT_ELSE,
        AST_STATEMENT_SWITCH,
        AST_STATEMENT_CASE,
        AST_ACCESS,
        AST_INT,
        AST_STRING,
        AST_CHAR,
        AST_FLOAT,
        AST_HEX,
        AST_BIN,
        AST_BINOP,
        AST_NOOP,
    } type;

    dataType dtype;
  
    list_t* children;
    char* name;
    char* stringValue;
    struct AST_STRUCT* value;
    struct AST_STRUCT* left;
    struct AST_STRUCT* right;
    int op;
    int intValue;
    int id;
    int stackIndex;
    int multiplier;
    struct AST_STRUCT* (*fptr)(struct VISITOR_STRUCT* visitor, struct AST_STRUCT* node, list_t* list);
    stackFrame_t* stackFrame;
} AST_t;

AST_t* initAST(int type);

#endif