#ifndef COBY_TOKEN_H
#define COBY_TOKEN_H
typedef struct TOKEN_STRUCT{
    char* value;
    enum{
        TOKEN_ID,
        TOKEN_STRING,
        TOKEN_INT,
        TOKEN_HEX,
        TOKEN_BIN,
        TOKEN_SEMICOLON,
        TOKEN_COMMA,
        TOKEN_DOT,
        TOKEN_COLON,
        TOKEN_LEFT_PAREN,
        TOKEN_RIGHT_PAREN,
        TOKEN_LEFT_BRACKET,
        TOKEN_RIGHT_BRACKET,
        TOKEN_LEFT_BRACE,
        TOKEN_RIGHT_BRACE,
        TOKEN_PLUS,
        TOKEN_INCREASE,
        TOKEN_MINUS,
        TOKEN_DECREASE,
        TOKEN_DIVIDE,
        TOKEN_MULTIPLY,
        TOKEN_POWER,
        TOKEN_MODULO,
        TOKEN_EQUALS,
        TOKEN_DOUBLE_EQUALS,
        TOKEN_GREATER_THAN,
        TOKEN_LESS_THAN,
        TOKEN_GREATER_EQUALS,
        TOKEN_LESS_EQUALS,
        TOKEN_CHAIN,
        TOKEN_BIT_OR,
        TOKEN_XOR,
        TOKEN_BIT_LEFT_SHIFT,
        TOKEN_BIT_RIGHT_SHIFT,
        TOKEN_NEGATE,
        TOKEN_IF,
        TOKEN_ELSEIF,
        TOKEN_EXTRACT,
        TOKEN_INJECT,
        TOKEN_CONSTANT,
        TOKEN_CONTAINS_VALUE,
        TOKEN_CONTAINS_KEY,
        TOKEN_BACK_EXTRACT
    } type;
} token_t;

token_t* initToken(char* value, int type);

#endif