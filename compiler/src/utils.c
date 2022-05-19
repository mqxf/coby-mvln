#include <stdlib.h>
#include <string.h>
#include "include/main.h"

char strToEsc(const char* str) {
    if (strlen(str) <= 1) return 0;
    if (str[0] != '\\') return 0;
    char c = str[1];

    switch (c) {
        case 'n': return '\n';
        case 't': return '\t';
        case 'r': return '\r';
        case '\\': return c;
        default: return c;
    }

    return c;
}

char* strFormat(char* str) {
    char* out = calloc(1, sizeof(char));
    unsigned int len = strlen(str);

    unsigned int i = 0;
    while (str[i] != '\0' && i < len) {
        out = realloc(out, (strlen(out) + 2) * sizeof(char));

        if (str[i] == '\\') {
            char escape = strToEsc((char[]){ str[i], str[MIN(i+1, len)], 0 });
            strcat(out, (char[]){escape, 0});
            i += 2;
        }
        else {
            strcat(out, (char[]){str[i], 0});
            i += 1;
        }
    }
    return out;
}