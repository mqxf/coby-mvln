#ifndef COBY_TYPES_H
#define COBY_TYPES_H

typedef enum{
    DATA_TYPE_STRING,
    DATA_TYPE_CHAR,
    DATA_TYPE_BOOLEAN,
    DATA_TYPE_INT,
    DATA_TYPE_FLOAT,
    DATA_TYPE_HEX,
    DATA_TYPE_BIN,
    DATA_TYPE_VOID, //might need to remove this
    DATA_TYPE_LIST,
    DATA_TYPE_COLLECTION,
    DATA_TYPE_LIBRARY,
    DATA_TYPE_UNKNOWN
} dataType;

int typenameToInt(const char* name);

#endif