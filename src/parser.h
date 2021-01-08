/* Parses input to give a 2D array */

#include <stdio.h>

#ifndef PARSE_H
#define PARSE_H

typedef struct {
    char **grid;
    size_t nr;
} Program;

void parse(Program* p);
void padrows(Program* p, int max_col);
void prettyprint(Program *p);

#endif