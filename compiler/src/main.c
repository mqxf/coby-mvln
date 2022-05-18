#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/main.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: cobyc <input file> [-o <output file>]\n");
        exit(1);
    }

    char* inFile;
    char* outFile;

    if (strcmp(argv[1], "-o") == 0) {
        if (argc < 4) {
            printf("Usage: cobyc [-o <output file>] <input file>\n");
            exit(1);
        }
        outFile = (char*) calloc(strlen(argv[2]), sizeof(char));
        inFile = (char*) calloc(strlen(argv[3]), sizeof(char));
        strcpy(outFile, argv[2]);
        strcpy(inFile, argv[3]);
    }
    else {
        if (argc < 3) {
            inFile = (char*) calloc(strlen(argv[1]), sizeof(char));
            strcpy(inFile, argv[1]);
            char* tok = strtok(argv[1], ".");
            outFile = (char*) calloc(strlen(tok) + 2, sizeof(char));
            strcpy(outFile, tok);
            strcat(outFile, ".s");
        }
        else {
            if (strcmp(argv[2], "-o") == 0) {
                if (argc < 4) {
                    printf("Usage: cobyc <input file> [-o <output file>]\n");
                    exit(1);
                }
                inFile = (char*) calloc(strlen(argv[1]), sizeof(char));
                strcpy(inFile, argv[1]);
                outFile = (char*) calloc(strlen(argv[3]), sizeof(char));
                strcpy(outFile, argv[3]);
            }
        }
    }

    printf("Taking code input file: %s\nGenerating assembly output file: %s\n", inFile, outFile);
    compile(inFile, outFile);
    free(inFile);
    free(outFile);
    return 0;
}