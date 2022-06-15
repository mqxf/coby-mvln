#include "include/main.h"

AST_t* initAST(unsigned int type) {
    AST_t* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;
    ast->children = initList(sizeof(struct AST_STRUCT*));
    return ast;
}