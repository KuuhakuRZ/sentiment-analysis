#include "functions.h"

struct words *wordsArray(const char *path, int *wordsCount){

    FILE *file;
    file = fopen(path, "r");

    char line[1024];
    *wordsCount = 0;

    // Allocate memory for the words array
    struct words *words_array = malloc(10000 * sizeof(struct words));
    if (words_array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Check if the file was opened successfully
    if (file == NULL) {
        fprintf(stderr, "Unable to open source file\n");
        return NULL;
    }

    // Read each line of the file
    while(fgets(line, sizeof(line), file)){

        char *token;
        token = strtok(line, "\t"); 
        // Get word, score, standard deviation, and SIS values from each line
        if (token != NULL) {
            words_array[*wordsCount].word = strdup(token); 
            token = strtok(NULL, "\t");
            words_array[*wordsCount].score = atof(token); 
            token = strtok(NULL, "\t");
            words_array[*wordsCount].SD = atof(token); 
            token = strtok(NULL, "\t[,\n"); 
            for (int i = 0; i < 10; i++) {
                words_array[*wordsCount].SIS_array[i] = atoi(token); 
                token = strtok(NULL, "\t[,\n"); 
            }
        (*wordsCount)++; 
        }    
    }
    fclose(file);

    // Reallocate memory for the words array to fit the actual number of words read
    struct words *temp = realloc(words_array, (*wordsCount) * sizeof(struct words));
    if (temp == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        free(words_array);
        return NULL;
    } else {
        words_array = temp;
    }

    return words_array;
}

void analysis_line(struct words *words_array, int *wordsCount, char *text) {
    char *token;
    float result = 0;
    int count = 0;

    char *line = strdup(text); // Create a duplicate of the input text
    token = strtok(text, " ,.!?");
    // Tokenize the text and perform sentiment analysis
    while (token != NULL) {
        for (int i = 0; i < (*wordsCount); i++) {
            // Search for the word in the words_array
            if (strcmp(words_array[i].word, token) == 0) { //Brute-force to solve
                result += words_array[i].score;
                break;
            }
        }
        count ++;
        token = strtok(NULL, " ,.!?");
    }

    // Calculate the average sentiment score for the line
    if (count > 0) {
        float output = result / count;
        printf("%-90s %.2f\n", line, output);
    } else {
        printf("%s none sentiment analysis\n", line);
    }
    // Free the heap
    free(line); 
}