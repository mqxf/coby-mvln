#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/main.h"

token_T* initToken(char* value, int type){
    token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->value = value;
    token->type = type;

    return token;
}