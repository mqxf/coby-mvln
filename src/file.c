#include "include/main.h"

char* cobyRead(const char* filename) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Could not read file '%s'\n", filename);
        exit(1);
    }

    char* buf = (char*) calloc(1, sizeof(char));
    buf[0] = '\0';

    while ((read = getline(&line, &len, fp)) != -1) {
        buf = (char*) realloc(buf, (strlen(buf) + strlen(line) + 1) * sizeof(char));
        strcat(buf, line);
    }

    fclose(fp);
    if (line)
        free(line);

    return buf;
}

void cobyWrite(const char* filename, const char* buf) {
    FILE * fp;

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Could not open file for writing '%s'\n", filename);
        exit(1);
    }

    fputs(buf, fp);
    fclose(fp);
}