#ifndef COBY_STACK_FRAME_H
#define COBY_STACK_FRAME_H

#include "main.h"

typedef struct STACK_FRAME_STRUCT {
    list_t* stack;
} stackFrame_t;

stackFrame_t* initStackFrame();

#endif