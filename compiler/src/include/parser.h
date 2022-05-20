#ifndef COBY_PARSER_H
#define COBY_PARSER_H

#include "main.h"
#include "AST.h"

typedef struct PARSER_STRUCT {
    lexer_t* lexer;
    token_t* token;
    size_t i;
    char c;
} parser_t;

parser_t* initParser(lexer_t* lexer);

token_t* parserEat(parser_t* parser, unsigned int type);

AST_t* parserParse(parser_t* parser);

AST_t* parseExpression(parser_t* parser);

AST_t* parseStatement(parser_t* parser);

AST_t* parseCompound(parser_t* parser);

#endif