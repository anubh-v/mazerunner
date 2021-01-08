#include <string>
#include <stack>

#ifndef THREAD_H
#define THREAD_H

class Thread {
    // move the program pointer one step in current direction
    public:
      std::string current_direction = "right";
      int program_pointer[2];
      std::stack<int> main_stack;
      std::stack<int> aux_stack;

      void move_to_next_inst() {
    
      }

};

#endif
