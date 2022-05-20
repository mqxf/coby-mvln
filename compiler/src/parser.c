#include "include/main.h"

parser_t* initParser(lexer_t* lexer) {
    parser_t* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->token = lexerNextToken(lexer);

    return parser;
}

token_t* parserEat(parser_t* parser, unsigned int type) {
    if (parser->token->type != type) {
        printf("[Parser]: Unexpected token: '%s', was expecting token with type: '%s'\n", tokenToString(parser->token), tokenTypeToString(type));
        exit(1);
    }

  parser->token = lexerNextToken(parser->lexer);
  return parser->token;
}

AST_t* parserParse(parser_t* parser) {
    return parseFile(parser);
}

AST_t* parseFile(parser_t* parser) {
    AST_t* ast = initAST(AST_FILE);
    while (parser->token->type != TOKEN_EOF) {
        list_t* children = initList(sizeof(struct AST_STRUCT));
        listPush(children, parseFunction(parser));
    }
}

AST_t* parseFunction(parser_t* parser) {

}