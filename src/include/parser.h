#ifndef COBY_PARSER_H
#define COBY_PARSER_H

#include "main.h"
#include "AST.h"

typedef struct PARSER_STRUCT {
    lexer_t* lexer;
    token_t* token;
    token_t** tokens;
    size_t size;
    size_t i;
} parser_t;

parser_t* initParser(lexer_t* lexer);

token_t* parserEat(parser_t* parser, unsigned int type);
AST_t* parserParse(parser_t* parser);
AST_t* parseConstant(parser_t* parser);
AST_t* parseVariable(parser_t* parser);
AST_t* parseList(parser_t* parser, char* name);

#endif