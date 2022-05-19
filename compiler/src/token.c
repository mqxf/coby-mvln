#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/main.h"

token_t* initToken(char* value, int type){
    token_t* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->value = value;
    token->type = type;

    return token;
}