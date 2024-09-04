#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char *load_words(const char *filename, int *word_count)
{
    char *words = NULL;
    size_t size = 0;
    int ch = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
    }

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        // Reallocate words to accommodate the new character
        char *temp = realloc(words, size + 1);
        if (temp == NULL) {
            perror("Error reallocating memory");
            free(words);
            fclose(file);
        }

        if (ch == ' ') {
            (*word_count)++;
        }
        words = temp;
        words[size] = (char) ch;
        size++;
    }

    // Add a null terminator at the end of the words
    char *temp = realloc(words, size + 1);
    if (temp == NULL) {
        perror("Error reallocating memory");
        free(words);
        fclose(file);
    }

    words = temp;
    words[size] = '\0';

    fclose(file);
    return words;
}

int main(int argc, char *argv[])
{
    if (argc < 3 || (strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "--dictionary") != 0)) {
        fprintf(stderr, "Usage: %s -d <wordlist_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int word_count = 0;
    char *words = load_words(argv[2], &word_count);

    printf("File content:\n%s", words);
}
