#include <string>
#include <stack>

class Thread {

    static const int RIGHT = 0;
    static const int LEFT = 1;
    static const int UP = 2;
    static const int DOWN = 3;

    public:
      int current_direction = RIGHT;
    public:
      int program_pointer[2]; // [x, y]
    public:
      std::stack<int> stack;
    
    // move the program pointer one step in current direction
    public:
      void move_to_next_inst() {
          switch(current_direction) {
              case RIGHT:
                  move_right();
                  break;
              case LEFT:
                  move_left();
                  break;
              case UP:
                  move_up();
                  break;
              case DOWN:
                  move_down();
                  break;
              default:
                  // error
                  break;
          }
      }

    // move right = move in positive x direction
    void move_right() {
        program_pointer[0]++;
    }

    // move left = move in negative x direction
    void move_left() {
        program_pointer[0]--;
    }

    // move up = move in negative y direction
    void move_up() {
        program_pointer[1]--;
    }

    // move down = move in positive y direction
    void move_down() {
        program_pointer[1]++;
    }
};
