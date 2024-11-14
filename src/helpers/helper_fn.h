#ifndef helper_fn_h
#define helper_fn_h

#include <stdio.h>
#include <stdlib.h>

ssize_t getline(char **line, size_t *len, FILE *stream) {
    size_t size = 64; // Initial buffer size
    size_t length = 0;
    *line = malloc(size);
    if (*line == NULL) return -1;

    int c;
    while ((c = fgetc(stream)) != EOF && c != '\n') {
        (*line)[length++] = c;

        // Resize buffer if needed
        if (length >= size) {
            size *= 2;
            *line = realloc(*line, size);
            if (*line == NULL) return -1;
        }
    }

    if (c == EOF && length == 0) {
        free(*line);
        *line = NULL;
        return -1;
    }

    (*line)[length] = '\0';
    *len = length;
    return length;
}

#endif


