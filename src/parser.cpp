#include "parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 10

void parse(Program *p) {
	char **grid = (char **) malloc(sizeof(char*) * SIZE);

    int c, i, j;
    c = i = j = 0;
    char *line = (char *) malloc(sizeof(char) * SIZE);
    while ((c = getchar()) != EOF) {
        if (i > 0 && i % SIZE == 0) {
            grid = (char **) realloc(grid, sizeof(char *) * ((i / SIZE) + 1) * SIZE);
        }

        if (j > 0 && j % SIZE == 0) {
            line = (char *) realloc(line, sizeof(char) * ((j / SIZE) + 1) * SIZE);
        }

        if (c == '\n') {
            line[j] = '\0';
            j = 0;

            grid[i] = line;
            line = (char *) malloc(sizeof(char) * SIZE);
            i++;
        } else {
            line[j] = c;
            j++;
        }
    }

    p->grid = grid;
    p->nr = i;
}

void prettyprint(Program *p) {
    int i = 0;
    while (i < p->nr) {
        printf("%s\n", p->grid[i]);
        i++;
    }
}

