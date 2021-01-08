#include <stdio.h>

#ifndef PARSE_H
#define PARSE_H

typedef struct {
    char **grid;
    size_t nr;
} Program;

void parse(Program* p);
void prettyprint(Program *p);

#endif