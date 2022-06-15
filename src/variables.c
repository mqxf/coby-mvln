#include "include/main.h"

variable_t** vars;
size_t size = 0;

int isValidName(char* name) {
    if (search(name) != -1) {
        return 0;
    }
    return isNotKeyword(name);
}

int isNotKeyword(char* name) {
    char* strs[16] = {"string", "char", "int", "float", "hex", "bin", "bool", "void", "list", "of", "collection", "library", "for", "while", "not", "null"};

    for (int i = 0; i < 16; i++) {
        if (strcmp(name, strs[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

int search(char* name) {
    for (size_t i = 0; i < size; i++) {
        if (strcmp(vars[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int getType(char* variable) {
    int i = search(variable);
    if (i == -1) {
        return -1;
    }
    return vars[i]->type;
}

void addVariable(char* variable, int type) {
    if (!vars) {
        vars = calloc(1, sizeof(struct VAR_STRUCT*));
        size = 1;
    }
    else {
        size++;
        vars = realloc(vars, sizeof(struct VAR_STRUCT*) * size);
    }

    variable_t* var = calloc(size, sizeof(struct VAR_STRUCT));
    var->type = type;
    var->name = variable;
    vars[size - 1] = var;
}