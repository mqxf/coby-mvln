#include "include/main.h"

AST_t* initAST(int type) {
    AST_t* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;

    if (type == AST_COMPOUND) {
        ast->children = initList(sizeof(struct AST_STRUCT*));
    }

    ast->stackFrame = (void*)0;
    ast->multiplier = 1;
    ast->dtype = DATA_TYPE_UNKNOWN;

    return ast;
}