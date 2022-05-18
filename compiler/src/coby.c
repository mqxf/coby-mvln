#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/main.h"


void compile(const char* inFile, const char* outFile) {
    char* src = cobyRead(inFile);


    //cobyWrite(outFile, compiled);
    free(src);
}