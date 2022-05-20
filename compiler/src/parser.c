#include "include/main.h"

AST_t* initParser(lexer_t* lexer) {
    parser_t* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->token = lexerNextToken(lexer);

    return parser;
}

token_t* parserEat(parser_t* parser, int type) {
    if (parser->token->type != type) {
        printf("[Parser]: Unexpected token: '%s', was expecting: '%s'\n", token_to_str(parser->token), token_type_to_str(type));
        exit(1);
    }

  parser->token = lexerNextToken(parser->lexer);
  return parser->token;
}

AST_t* parserParse(parser_t* parser) {
    parserParseCompound(parser);
}

AST_t* parseExpression(parser_t* parser) {

}

AST_t* parseStatement(parser_t* parser) {

    if (strcmp(parser->token->value, "back") == 0) {
        AST_t* ast = init_ast(AST_STATEMENT_RETURN);
        parserEat(parser, TOKEN_ID);
        ast->value = parseExpression(parser);
    }
    else if (parser->token->type == TOKEN_IF) {
        AST_t* ast = init_ast(AST_STATEMENT_IF);
        parserEat(parser, TOKEN_IF);
        ast->value = parseExpression(parser);
    }
    else if (parser->token->type == TOKEN_ELSE_IF){
        AST_t* ast = init_ast(AST_STATEMENT_ELSE_IF);
        parserEat(parser, TOKEN_ELSE_IF);
        ast->value = parseExpression(parser);
    }
    {
        /* code */
    }
    
    else {
        return parseExpression(parser);
    }

}

AST_t* parseCompound(parser_t* parser) {
    unsigned char shouldClose = 0;

    if (parser->token->type == TOKEN_LEFT_BRACE) {
        parserEat(parser, TOKEN_LEFT_BRACE);
        shouldClose = 1;
    }

    AST_t* compound = initAst(AST_COMPOUND);

    while (parser->token->type != TOKEN_EOF && parser->token->type != TOKEN_RIGHT_BRACE) {

        listPush(compound->children, parseStatement(parser));

        if (parser->token->type == TOKEN_SEMICOLON)
        parserEat(parser, TOKEN_SEMICOLON);
    }

    if (shouldClose) {
        parserEat(parser, TOKEN_RIGHT_BRACE);
    }

    return compound;
}