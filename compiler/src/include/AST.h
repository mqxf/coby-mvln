#ifndef COBY_AST_H
#define COBY_AST_H

#include "main.h"
#include "types.h"
#include "list.h"
#include "stackFrame.h"

struct VISITOR_STRUCT;

typedef struct AST_STRUCT {
    enum {
        AST_TOKEN_
    } type;

    dataType dtype;
  
    list_t* children;
    char* name;
    char* strValue;
    int intValue;
    float floatValue;

} AST_t;

AST_t* initAST(int type);

#endif