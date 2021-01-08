#include <stack>
#include "thread.h"
#include "src/parser.h"
#include "instruction_set.h"

void turn_left(Thread thread);
void turn_right(Thread thread);
void is_neighbour(int x, int y, int num_rows, int num_cols, char** grid);

void update_direction(Program program, Thread thread) {

    // find number of neighbours
    int thread_x = thread.program_pointer[0];
    int thread_y = thread.program_pointer[1];

    bool neighbours[4]; // [left, right, up, down] neighbour (true if that neighbour exists)
    neighbours[0] = false;
    neighbours[1] = false;
    neighbours[2] = false;
    neighbours[3] = false;
    int num_neighbours;


    // check neighbouring squares in all 4 directions

    if (is_neighbour(thread_x + 1, thread_y, program.nr, program.nr, program.grid)) {
        neighbours[1] = true; // there is a neighbour on the right
        num_neighbours++;
    }

    if (is_neighbour(thread_x - 1, thread_y, program.nr, program.nr, program.grid)) {
        neighbours[0] = true;
        num_neighbours++;
    }

    if (is_neighbour(thread_x, thread_y + 1, program.nr, program.nr, program.grid)) {
        neighbours[3] = true; // there is neighbour below
        num_neighbours++;
    }

    if (is_neighbour(thread_x, thread_y - 1, program.nr, program.nr, program.grid)) {
        neighbours[2] = true; // there is neighbour above
        num_neighbours++;
    }

    // apply the direction update rules, once number of neighbours is known
    switch(num_neighbours) {
        case 1:
            apply_one_neighbour_rule(neighbours, thread);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            // error
            break;

    }


}

void is_neighbour(int x, int y, int num_rows, int num_cols, char** grid) {
    if (y >= num_cols) {
          return false; // point is below the grid
    }

    if (y < 0) {
        return false; // point is above the grid
    }

    if (x >= num_rows) {
        return false;  // point is to the right of the grid
    }

    if (x < 0) {
       return false;  // point is to the left of the grid
    }

    // point is inside the grid
    // check if is a valid instruction
    char* row = grid[y];
    char current_char = row[x];
    return is_instruction(current_char);
}

// neighbours = [left, right, up, down]
void apply_one_neighbour_rule(bool neighbours[4], Thread thread) {
    if (neighbour[0]) {
        thread.current_direction = Thread.LEFT;
    } else if (neighbour[1]) {
        thread.current_direction = Thread.RIGHT;
    } else if (neighbour[2]) {
        thread.current_direction = Thread.UP;
    } else if (neighbour[3]) {
        thread,current_direction = Thread.DOWN;
    }
}

void apply_four_neighbour_rule(bool neighbours[4], Thread thread) {
    std::stack<int> main_stack = thread.main_stack;
    int top_element = main_stack.top();

    if (top_element == 0) {
        // keep going straight - no need to change direction
    } else if (top_element < 0) {
        // turn left
        turn_left(Thread thread);
    } else {
        turn_right(Thread thread);
    }
}

void turn_left(Thread thread) {

    if (thread.current_direction = Thread.UP) {
        thread.current_direction = Thread.LEFT;
    } else if (thread.current_direction = Thread.DOWN) {
        thread.current_direction = Thread.RIGHT;
    } else if (thread.current_direction = Thread.LEFT) {
        thread.current_direction = Thread.DOWN;
    } else { // current direction is rightwards
        thread.current_direction = Thread.UP;
    }

}

void turn_right(Thread thread) {

    if (thread.current_direction = Thread.UP) {
        thread.current_direction = Thread.RIGHT;
    } else if (thread.current_direction = Thread.DOWN) {
        thread.current_direction = Thread.LEFT;
    } else if (thread.current_direction = Thread.LEFT) {
        thread.current_direction = Thread.UP;
    } else { // current direction is rightwards
        thread.current_direction = Thread.DOWN;
    }

}


