#include "parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 10

void parse(Program *p) {
	char **grid = (char **) malloc(sizeof(char*) * SIZE);

    int c, i, j;
    c = i = j = 0;
    int max_col = 0;
    char *line = (char *) malloc(sizeof(char) * SIZE);
    while ((c = getchar()) != EOF) {
        if (i > 0 && i % SIZE == 0) {
            grid = (char **) realloc(grid, sizeof(char *) * ((i / SIZE) + 1) * SIZE);
        }

        if (j > 0 && j % SIZE == 0) {
            line = (char *) realloc(line, sizeof(char) * ((j / SIZE) + 1) * SIZE);
        }

        if (c == '\n') {
            // line[j] = '\0';
            j = 0;

            grid[i] = line;
            line = (char *) malloc(sizeof(char) * SIZE);
            i++;
        } else {
            line[j] = c;
            j++;
        }

        max_col = max_col > j ? max_col : j;
    }

    // printf("%zu\n", p->nr);
    // padrows(p, max_col);
    p->grid = grid;
    p->nr = (size_t) i;
}

// void padrows(Program *p, int max_col) {
//     int i = 0;
//     printf("her\n");
//     while (i < p->nr) {
//         //printf("her2\n");
//         //size_t l = ;
//         //printf("%zu\n", strlen(p->grid[i]));
//         // if (l < max_col) {
//         //     p->grid[i] = (char *) realloc(p->grid[i], sizeof(char) * max_col);
//         // }

//         // printf("here\n");
//         // while (l < max_col) {
//         //     p->grid[i][l] = 'p';
//         //     l++;
//         // }
//         // printf("heres\n");
//         i = i + 1;
//     }
// }

void prettyprint(Program *p) {
    int i = 0;
    while (i < p->nr) {
        printf("%s\n", p->grid[i]);
        i++;
    }
}


