#include <ctype.h>
#include "include/main.h"

lexer_t* initLexer(char* src) {
    lexer_t* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->len = strlen(src);
    lexer->i = 0;
    lexer->c = src[0];

    return lexer;
}

char lexerPeek(lexer_t* lexer, int offset) {
    return lexer->src[lexer->i + offset];
}

lexer_t* lexerAdvance(lexer_t* lexer) {
    if (lexer->i < lexer->len) {
        lexer->i++;
        lexer->c = lexer->src[lexer->i];
    }
    return lexer;
}

lexer_t* lexerSkipWhiteSpace(lexer_t* lexer) {
    while(lexer->c == 13 || lexer->c == 10 || lexer->c == ' ' || lexer->c == '\t'){
        lexerAdvance(lexer);
    }
    return lexer;
}

lexer_t* lexerSkipComment(lexer_t* lexer) {
    if (lexer->c == '.' && lexerPeek(lexer, 1) == '.') {
        if (lexerPeek(lexer, 2) == '.') {
            lexerAdvance(lexer);
            for (;;) {
                if (lexer->c == '.' && lexerPeek(lexer, 1) == '.' && lexerPeek(lexer, 2) == '.') {
                    lexerAdvance(lexer); 
                    lexerAdvance(lexer); 
                    lexerAdvance(lexer);
                    break;
                }
                lexerAdvance(lexer);
            }
        }
        else {
            while (lexer->c !='\n') lexerAdvance(lexer);
        }
        lexerSkipWhiteSpace(lexer);
        lexerSkipComment(lexer);
    }
    return lexer;
}

token_t* lexerAdvanceWith(lexer_t* lexer, token_t* token) {
    for (size_t i = 0; i < strlen(token->value); i++) lexerAdvance(lexer);
    return token;
}

token_t* lexerNextId(lexer_t* lexer) {
    char* value = calloc(1, sizeof(char));
    while (isalnum(lexer->c)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexerAdvance(lexer);
    }
    if (strcmp(value, "not") == 0) return initToken(value, TOKEN_NEGATE);
    return initToken(value, TOKEN_ID);
}

token_t* lexerNextNumber(lexer_t* lexer) {
    if (lexer->c == '0') {
        if (lexerPeek(lexer, 1) == 'x') {
            lexerAdvance(lexer);
            lexerAdvance(lexer);
            return lexerNextHexadecimal(lexer);
        }
        if (lexerPeek(lexer, 1) == 'b') {
            lexerAdvance(lexer);
            lexerAdvance(lexer);
            return lexerNextBinary(lexer);
        }
    }

    //TODO: check for float

    char* value = calloc(1, sizeof(char));
    while (isdigit(lexer->c)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexerAdvance(lexer);
    }
    return initToken(value, TOKEN_INT);   
}

token_t* lexerNextFloat(lexer_t* lexer) {

}

token_t* lexerNextHexadecimal(lexer_t* lexer) {
    char* value = calloc(1, sizeof(char));
    while (isxdigit(lexer->c)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexerAdvance(lexer);
    }
    return initToken(value, TOKEN_HEX);
}

token_t* lexerNextBinary(lexer_t* lexer) {
    char* value = calloc(1, sizeof(char));
    while (lexer->c == '0' || lexer->c == '1') {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexerAdvance(lexer);
    }
    return initToken(value, TOKEN_BIN);
}

token_t* lexerNextString(lexer_t* lexer) {
    char* value = calloc(1, sizeof(char));
    lexerAdvance(lexer);
    while (lexer->c != '"') {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexerAdvance(lexer);
    }
    lexerAdvance(lexer);
    char* formatted = strFormat(value);
    free(value);
    return initToken(formatted, TOKEN_STRING);
}

token_t* lexerNextChar(lexer_t* lexer) {
    char* value = calloc(1, sizeof(char));
    lexerAdvance(lexer);
    while (lexer->c != '\'') {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexerAdvance(lexer);
    }
    lexerAdvance(lexer);
    char* formatted = strFormat(value);
    free(value);
    return initToken(formatted, TOKEN_CHAR);
}

token_t* lexerNextToken(lexer_t* lexer) {
    lexerSkipWhiteSpace(lexer);
    lexerSkipComment(lexer);

    if (isalpha(lexer->c)) {
        return lexerNextId(lexer);
    }
    if(isdigit(lexer->c)){
        return lexerNextNumber(lexer);
    }

    //switch, if token is something that can be used in multi charcter token, check for that first with lexerPeek();
    //parse as string at token ""
    //parse as char at token ''


    switch (lexer->c){
        case '-':
            if (lexerPeek(lexer, 1) == '>') return lexerAdvanceWith(lexer, initToken("->", TOKEN_EXTRACT));
            if (lexerPeek(lexer, 1) == '-') return lexerAdvanceWith(lexer, initToken("--", TOKEN_DECREASE));
            if (lexerPeek(lexer, 1) == '?') return lexerAdvanceWith(lexer, initToken("-?", TOKEN_CONTAINS_KEY));
            return lexerAdvanceWith(lexer, initToken("-", TOKEN_MINUS));
        case '+':
            if (lexerPeek(lexer, 1) == '+') return lexerAdvanceWith(lexer, initToken("++", TOKEN_INCREASE));
            return lexerAdvanceWith(lexer, initToken("+", TOKEN_PLUS));
        case '=':
            if (lexerPeek(lexer, 1) == '>') return lexerAdvanceWith(lexer, initToken("=>", TOKEN_INJECT));
            if (lexerPeek(lexer, 1) == '=') return lexerAdvanceWith(lexer, initToken("==", TOKEN_DOUBLE_EQUALS));
            if (lexerPeek(lexer, 1) == '?') return lexerAdvanceWith(lexer, initToken("=?", TOKEN_CONTAINS_VALUE));
            return lexerAdvanceWith(lexer, initToken("=", TOKEN_EQUALS));  
        case '&': 
            if (lexerPeek(lexer, 1) == '&') return lexerAdvanceWith(lexer, initToken("&&", TOKEN_AND));
            if (lexerPeek(lexer, 1) == '?') return lexerAdvanceWith(lexer, initToken("&?", TOKEN_ELSE_IF));
            return lexerAdvanceWith(lexer, initToken("&", TOKEN_CHAIN));
        case '<':
            if(lexerPeek(lexer, 1) == '=') return lexerAdvanceWith(lexer, initToken("<=", TOKEN_LESS_EQUALS));
            if(lexerPeek(lexer, 1) == '-') return lexerAdvanceWith(lexer, initToken("<-", TOKEN_BACK_EXTRACT));
            if(lexerPeek(lexer, 1) == '<') return lexerAdvanceWith(lexer, initToken("<<", TOKEN_BIT_LEFT_SHIFT));
            return lexerAdvanceWith(lexer, initToken("<", TOKEN_LESS_THAN));
        case '|': 
            if(lexerPeek(lexer, 1) == '|') return lexerAdvanceWith(lexer, initToken("||", TOKEN_OR));
            return lexerAdvanceWith(lexer, initToken("|", TOKEN_BIT_OR));
        case '>':
            if(lexerPeek(lexer, 1) == '=') return lexerAdvanceWith(lexer, initToken(">=", TOKEN_GREATER_EQUALS));
            if(lexerPeek(lexer, 1) == '>') return lexerAdvanceWith(lexer, initToken(">>", TOKEN_BIT_RIGHT_SHIFT));
            return lexerAdvanceWith(lexer, initToken(">", TOKEN_GREATER_THAN));
        case '*':
            if (lexerPeek(lexer, 1) == '*') return lexerAdvanceWith(lexer, initToken("**", TOKEN_POWER));
            return lexerAdvanceWith(lexer, initToken("*", TOKEN_MULTIPLY));
        case '\'': return lexerNextChar(lexer);
        case '\"': return lexerNextString(lexer);
        case ',': return lexerAdvanceWith(lexer, initToken(",", TOKEN_COMMA));
        case ';': return lexerAdvanceWith(lexer, initToken(";", TOKEN_SEMICOLON));
        case ':': return lexerAdvanceWith(lexer, initToken(":", TOKEN_COLON));
        case '^': return lexerAdvanceWith(lexer, initToken("^", TOKEN_XOR));
        case '%': return lexerAdvanceWith(lexer, initToken("%", TOKEN_MODULO));
        case '!': return lexerAdvanceWith(lexer, initToken("!", TOKEN_NEGATE));
        case '#': return lexerAdvanceWith(lexer, initToken("#", TOKEN_CONSTANT));
        case '?': return lexerAdvanceWith(lexer, initToken("?", TOKEN_IF)); 
        case '(': return lexerAdvanceWith(lexer, initToken("(", TOKEN_LEFT_PAREN));
        case '[': return lexerAdvanceWith(lexer, initToken("[", TOKEN_LEFT_BRACKET));
        case '{': return lexerAdvanceWith(lexer, initToken("{", TOKEN_LEFT_BRACE));
        case ')': return lexerAdvanceWith(lexer, initToken(")", TOKEN_RIGHT_PAREN));
        case ']': return lexerAdvanceWith(lexer, initToken("]", TOKEN_RIGHT_BRACKET));
        case '}': return lexerAdvanceWith(lexer, initToken("}", TOKEN_RIGHT_BRACE));
        case '.': return lexerAdvanceWith(lexer, initToken(".", TOKEN_DOT));
        case '/': return lexerAdvanceWith(lexer, initToken("/", TOKEN_DIVIDE));
        case '@': return lexerAdvanceWith(lexer, initToken("@", TOKEN_ADDRESS));
        case '\0': break;
        default:
            printf("Invalid token %c, %d", lexer->c, lexer->c);
            exit(1);
            break;
    }   

    return initToken(0, TOKEN_EOF);

}