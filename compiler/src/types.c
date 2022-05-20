#include "include/main.h"

int typenameToInt(const char* name) {
    if (strcmp(name, "int") == 0) return DATA_TYPE_INT;
    if (strcmp(name, "float") == 0) return DATA_TYPE_FLOAT;
    if (strcmp(name, "hex") == 0) return DATA_TYPE_HEX;
    if (strcmp(name, "bin") == 0) return DATA_TYPE_BIN;
    if (strcmp(name, "char") == 0) return DATA_TYPE_CHAR;
    if (strcmp(name, "str") == 0) return DATA_TYPE_STRING;
    if (strcmp(name, "void") == 0) return DATA_TYPE_VOID; //might need to remove
    if (strcmp(name, "list") == 0) return DATA_TYPE_LIST;
    if (strcmp(name, "collection") == 0) return DATA_TYPE_COLLECTION;
    if (strcmp(name, "library") == 0) return DATA_TYPE_LIBRARY;
    if (strcmp(name, "bool") == 0) return DATA_TYPE_BOOLEAN;

    return DATA_TYPE_UNKNOWN;
}