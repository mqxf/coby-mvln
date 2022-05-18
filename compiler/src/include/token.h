#ifndef COBY_TOKEN_H
#define COBY_TOKEN_H
typedef struct TOKEN_STRUCT{
    char* value;
    enum{
        TOKEN_ID,
        TOKEN_STRING,
        TOKEN_INT,
        TOKEN_SEMICOLON,
        TOKEN_COMMA,
        TOKEN_DOT,
        TOKEN_COLON,
        TOKEN_LEFT_PER,
        TOKEN_RIGHT_PER,
        TOKEN_LEFT_BRACKET,
        TOKEN_RIGHT_BRACKET,
        TOKEN_LEFT_BRACE,
        TOKEN_RIGHT_BRACE,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_DIVIDE,
        TOKEN_MULTIPLY,
        TOKEN_MODULO,
        TOKEN_EQUALS,
        TOKEN_DOUBLE_EQUALS,
        TOKEN_LEFT_ARROW,
        TOKEN_RIGHT_ARROW,
        TOKEN_BIT_AND,
        TOKEN_BIT_OR,
        TOKEN_BIT_LEFT_SHIFT,
        TOKEN_BIT_RIGHT_SHIFT,
        TOKEN_EXCLAMATION_MARK,
    } type;
} token_T;

token_T* initToken(char* value, int type);

#endif