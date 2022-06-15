#ifndef COBY_VARIABLES_H
#define COBY_VARIABLES_H

typedef struct VAR_STRUCT {
    char* name;
    unsigned int type;
} variable_t;

int isValidName(char* name);

int search(char* name);

int isNotKeyword(char* name);

int getType(char* variable);

void addVariable(char* variable, int type);

#endif