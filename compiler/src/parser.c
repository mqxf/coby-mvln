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
    return parseCompound(parser);
}

AST_t* parseExpression(parser_t* parser) {

}

AST_t* parseStatement(parser_t* parser) {
    if (strcmp(parser->token->value, "back") == 0) {
        AST_t* ast = initAST(AST_STATEMENT_RETURN);
        parserEat(parser, TOKEN_ID);
        ast->value = parseExpression(parser);
        return ast;
    }
    else if (parser->token->type == TOKEN_IF) {
        AST_t* ast = initAST(AST_STATEMENT_IF);
        parserEat(parser, TOKEN_IF);
        ast->value = parseExpression(parser);
        return ast;
    }
    else if (parser->token->type == TOKEN_ELSE_IF){
        AST_t* ast = initAST(AST_STATEMENT_ELSE_IF);
        parserEat(parser, TOKEN_ELSE_IF);
        ast->value = parseExpression(parser);
        return ast;
    }
    else if (parser->token->type == TOKEN_CHAIN) {
        lexerSkipWhiteSpace(parser->lexer);
        lexerSkipComment(parser->lexer);
        if (parser->lexer->c == '{') {
            AST_t* ast = initAST(AST_STATEMENT_ELSE);
            parserEat(parser, TOKEN_CHAIN);
            ast->value = parseExpression(parser);
            return ast;
        }
        else if (parser->lexer->c == '(') {
            AST_t* ast = initAST(AST_STATEMENT_CASE);
            parserEat(parser, TOKEN_CHAIN);
            ast->value = parseExpression(parser);
            return ast;
        }
        else{
            return parseExpression(parser);
        }
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

    AST_t* compound = initAST(AST_COMPOUND);

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