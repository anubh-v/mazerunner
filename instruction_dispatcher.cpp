#include <stack>


// Return 0 if the current thread of execution is complete (i.e. @ char encountered)
int eval_instruction(char instruction, std::stack<int> stack) {

    switch(instruction) {
        case '@':
          return 0;
        default:
          // error! unexpected instruction
          break;
    }

}
