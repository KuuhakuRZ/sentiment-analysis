#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct words { 
    char *word; 
    float score; 
    float SD;
    int SIS_array [10]; 
};

struct words * wordsArray(const char *path, int *wordsCount);
void analysis_line(struct words *words_array, int *wordsCount, char *text);

#endif /* FUNCTIONS_H */