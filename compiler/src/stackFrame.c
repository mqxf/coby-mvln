#include "include/main.h"

stackFrame_t* initStackFrame() {
    stackFrame_t* stackFrame = calloc(1, sizeof(struct STACK_FRAME_STRUCT));
    stackFrame->stack = initList(sizeof(char*));

    return stackFrame;
}