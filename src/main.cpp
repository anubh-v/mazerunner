#include "parser.h"
#include "interpreter.h"

int main(void) {
    Program p;
    parse(&p);
    prettyprint(&p);
    interpret(p);
}
