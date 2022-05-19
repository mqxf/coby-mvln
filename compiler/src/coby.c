#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/main.h"


void compile(const char* inFile, const char* outFile) {
    char* src = cobyRead(inFile);

    lexer_t* lexer = initLexer(src);
    token_t* token;

    while((token = lexerNextToken(lexer))->type != TOKEN_EOF) {
        printf("%s", tokenToString(token));
    }

    //cobyWrite(outFile, compiled);
    free(src);
}