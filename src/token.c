#include "include/main.h"

token_t* initToken(char* value, int type){
    token_t* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->value = value;
    token->type = type;

    return token;
}

const char* tokenTypeToString(int type) {
    switch (type) {
        case TOKEN_ID: return "TOKEN_ID";
        case TOKEN_STRING: return "TOKEN_STRING";
        case TOKEN_CHAR: return "TOKEN_CHAR";
        case TOKEN_INT: return "TOKEN_INT";
        case TOKEN_HEX: return "TOKEN_HEX";
        case TOKEN_BIN: return "TOKEN_BIN";
        case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";
        case TOKEN_COMMA: return "TOKEN_COMMA";
        case TOKEN_DOT: return "TOKEN_DOT";
        case TOKEN_COLON: return "TOKEN_COLON";
        case TOKEN_LEFT_PAREN: return "TOKEN_RIGHT_PAREN";
        case TOKEN_RIGHT_PAREN: return "TOKEN_RIGHT_PAREN";
        case TOKEN_LEFT_BRACKET: return "TOKEN_LEFT_BRACKET";
        case TOKEN_RIGHT_BRACKET: return "TOKEN_RIGHT_BRACKET";
        case TOKEN_LEFT_BRACE: return "TOKEN_LEFT_BRACE";
        case TOKEN_RIGHT_BRACE: return "TOKEN_RIGHT_BRACE";
        case TOKEN_PLUS: return "TOKEN_PLUS";
        case TOKEN_INCREASE: return "TOKEN_INCREASE";
        case TOKEN_MINUS: return "TOKEN_MINUS";
        case TOKEN_DECREASE: return "TOKEN_DECREASE";
        case TOKEN_DIVIDE: return "TOKEN_DIVIDE";
        case TOKEN_MULTIPLY: return "TOKEN_MULTIPLY";
        case TOKEN_POWER: return "TOKEN_POWER";
        case TOKEN_MODULO: return "TOKEN_MODULO";
        case TOKEN_EQUALS: return "TOKEN_EQUALS";
        case TOKEN_DOUBLE_EQUALS: return "TOKEN_DOUBLE_EQUALS";
        case TOKEN_GREATER_THAN: return "TOKEN_GREATER_THAN";
        case TOKEN_LESS_THAN: return "TOKEN_LESS_THAN";
        case TOKEN_GREATER_EQUALS: return "TOKEN_GRATER_EQUALS";
        case TOKEN_LESS_EQUALS: return "TOKEN_LESS_EQUALS";
        case TOKEN_CHAIN: return "TOKEN_CHAIN";
        case TOKEN_AND: return "TOKEN_AND";
        case TOKEN_OR: return "TOKEN_OR";
        case TOKEN_BIT_OR: return "TOKEN_BIT_OR";
        case TOKEN_XOR: return "TOKEN_XOR";
        case TOKEN_BIT_LEFT_SHIFT: return "TOKEN_BIT_LEFT_SHIFT";
        case TOKEN_BIT_RIGHT_SHIFT: return "TOKEN_BIT_RIGHT_SHIFT";
        case TOKEN_NEGATE: return "TOKEN_NEGATE";
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_ELSE_IF: return "TOKEN_ELSE_IF";
        case TOKEN_EXTRACT: return "TOKEN_EXTRACT";
        case TOKEN_INJECT: return "TOKEN_INJECT";
        case TOKEN_CONSTANT: return "TOKEN_CONSTANT";
        case TOKEN_CONTAINS_VALUE: return "TOKEN_CONTAINS_VALUE";
        case TOKEN_CONTAINS_KEY: return "TOKEN_CONTAINS_KEY";
        case TOKEN_BACK_EXTRACT: return "TOKEN_BACK_EXTRACT";
        case TOKEN_ADDRESS: return "TOKEN_ADDRESS";
        case TOKEN_EOF: return "TOKEN_EOF";
        default: return "invalid token type";
    }
}

char* tokenToString(token_t* token) {
    const char* type = tokenTypeToString(token->type);
    const char* template = "<TOKEN -> type = '%s', id= %d, val = \"%s\">\n";
    char* string = calloc(strlen(template) + strlen(type) + strlen(token->value) + 4, sizeof(char));
    sprintf(string, template, type, token->type, token->value);
    return string;
}