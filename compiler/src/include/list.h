#ifndef COBY_LIST_H
#define COBY_LIST_H

#include <stdlib.h>

typedef struct LIST_STRUCT {
  void** items;
  size_t size;
  size_t itemSize;
} list_t;

list_t* initList(size_t itemSize);
void listPush(list_t* list, void* item);
int listIndexofString(list_t* list, char* item);

#endif