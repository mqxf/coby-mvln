#ifndef COBY_LEXER_H
#define COBY_LEXER_H
#include <stdlib.h>
typedef struct LEXER_STRUCT {
    char* src;
    size_t len;
    size_t i;
    char c;
} lexer_t;

lexer_t* initLexer(char* src);

lexer_t* lexerAdvance(lexer_t* lexer);
token_t* lexerAdvanceWith(lexer_t* lexer, token_t* token);
char lexerPeek(lexer_t* lexer, int offset);

lexer_t* lexerSkipComment(lexer_t* lexer);
lexer_t* lexerSkipWhiteSpace(lexer_t* lexer);

token_t* lexerNextToken(lexer_t* lexer);

token_t* lexerNextId(lexer_t* lexer);

token_t* lexerNextNumber(lexer_t* lexer);
token_t* lexerNextFloat(lexer_t* lexer);
token_t* lexerNextHexadecimal(lexer_t* lexer);
token_t* lexerNextBinary(lexer_t* lexer);

token_t* lexerNextString(lexer_t* lexer);
token_t* lexerNextChar(lexer_t* lexer);

#endif