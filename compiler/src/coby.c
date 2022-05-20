#include "include/main.h"


void compile(const char* inFile, const char* outFile) {
    char* src = cobyRead(inFile);

    lexer_t* lexer = initLexer(src);
    parser_t* parser = initParser(lexer);
    AST_t* root = parserParse(parser);

    //cobyWrite(outFile, compiled);
    free(src);
}