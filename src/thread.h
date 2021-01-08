#include <string>
#include <stack>

#ifndef THREAD_H
#define THREAD_H

class Thread {
  public:
    static const int LEFT = 0;
    static const int RIGHT = 1;
    static const int UP = 2;
    static const int DOWN = 3;

    int current_direction = RIGHT;
    int program_pointer[2]; // [x, y]
    std::stack<int> main_stack;
    std::stack<int> aux_stack;
  
    // move the program pointer one step in current direction
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

#endif
