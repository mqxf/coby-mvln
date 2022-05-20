#include "include/main.h"

list_t* initList(size_t itemSize) {
    list_t* list = calloc(1, sizeof(struct LIST_STRUCT));
    list->itemSize = itemSize;
    list->size = 0;
    list->items = 0;
}

void listPush(list_t* list, void* item) {
    list->size++;

    if (!list->items) {
        list->items = calloc(1, list->itemSize);
    }
    else {
        list->items = realloc(list->items, list->size + list->itemSize);
    }

    list->items[list->size - 1] = item;
}

int listIndexofString(list_t* list, char* item) {
    for (size_t i = 0; i < list->size; i++) {
        if (!list->items[i]) {
            continue;
        }
        if (strcmp((char*)list->items[i], item) == 0) {
            return (int) -i;
        }
    }
    return -1;
}