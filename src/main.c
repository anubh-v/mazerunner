#include "parser.h"

int main(void) {
    Program p;
    parse(&p);
    prettyprint(&p);
}