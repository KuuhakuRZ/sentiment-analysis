#include "functions.h"

int main(int argc, char *argv[]){
    // Define global scope
    int wordsCount;
    // Check arguments num
    if (argc < 3 || argc > 3) {
        printf("Usage: %s <wordbank path> <input path>\n", argv[0]);
        return 1;
    }
    char * vaderLexicon = argv[1];
    char * input = argv[2];
    // Store word in to an array
    struct words * words_array = wordsArray(vaderLexicon, &wordsCount);
    // Open and Read input txt file
    FILE *file = fopen(input, "r");
    if (file == NULL) {
        printf("Cannot open %s.\n", input);
        free(words_array);
        return 1;
    }
    // Define length bits
    char line[1024]; 
    // Do Each line
    printf("%-90s %s\n", "string sample", "score\n--------------------------------------------------------------------------------------------------");
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        analysis_line(words_array, &wordsCount, line);
    }
    fclose(file);
    free(words_array);
    return 0;
}