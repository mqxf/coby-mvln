#include "include/main.h"


void compile(const char* inFile, const char* outFile) {
    char* src = cobyRead(inFile);

    lexer_t* lexer = initLexer(src);

    //token_t* token;

    //while ((token = lexerNextToken(lexer))->type != TOKEN_EOF) {
    //    printf("%s", tokenToString(token));
    //}

    parser_t* parser = initParser(lexer);
    AST_t* root = parserParse(parser);
    
    for (size_t i = 0; i < root->children->size; i++) {
        AST_t* temp = (AST_t*) root->children->items[i];
        if (temp->dType == DATA_TYPE_STRING) {
            printf("%s, %s\n", temp->name, temp->strValue);
        }
        else if (temp->dType == DATA_TYPE_CHAR) {
            printf("%s, %c\n", temp->name, temp->charValue);
        }
        else {
            printf("%s, %ld\n", temp->name, temp->longValue);
        }
    }
    //cobyWrite(outFile, compiled);
    
    free(src);
}