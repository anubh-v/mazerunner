#include <stack>
#include "thread.h"
#include "parser.h"
#include "instruction_set.h"

void turn_left(Thread thread);
void turn_right(Thread thread);
bool is_neighbour(int x, int y, int num_rows, int num_cols, char** grid);
void apply_one_neighbour_rule(bool neighbours[4], Thread thread);
void apply_two_neighbour_rule(bool neighbours[4], Thread thread);
void apply_three_neighbour_rule(bool neighbours[4], Thread thread);
void apply_four_neighbour_rule(bool neighbours[4], Thread thread);
void turn_left(Thread thread);
void turn_right(Thread thread);
void turn_back(Thread thread);
bool wall_ahead(bool neighbours[], Thread thread);
bool came_from(bool neighbours[], Thread thread);
bool go_other_direction(bool neighbours[], Thread thread);


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
            apply_three_neighbour_rule(neighbours, thread);
            break;
        case 4:
            apply_four_neighbour_rule(neighbours, thread);
            break;
        default:
            // error
            break;

    }


}

bool is_neighbour(int x, int y, int num_rows, int num_cols, char** grid) {
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
// Go towards the one available direction
void apply_one_neighbour_rule(bool neighbours[4], Thread thread) {
    if (neighbours[0]) {
        thread.current_direction = Thread::LEFT;
    } else if (neighbours[1]) {
        thread.current_direction = Thread::RIGHT;
    } else if (neighbours[2]) {
        thread.current_direction = Thread::UP;
    } else if (neighbours[3]) {
        thread.current_direction = Thread::DOWN;
    }
}

void apply_two_neighour_rule(bool neighbours[4], Thread thread) {
    
    // check if one of the neigbhours was just passed by the program (we do not go backwards)
    if (came_from(neighbours, thread)) {
        go_other_direction(neighbours, thread);
    } else {
        // go straight
    }
}

void apply_three_neighbour_rule(bool neighbours[4], Thread thread) {

    // apply 4 neighbours' rule, then reverse direction if heading into wall
    apply_four_neighbour_rule(neighbours, thread);

    if (wall_ahead(neighbours, thread)) {
        turn_back(thread);
    }

}

void apply_four_neighbour_rule(bool neighbours[4], Thread thread) {
    std::stack<int> main_stack = thread.main_stack;
    int top_element = main_stack.top();

    if (top_element == 0) {
        // keep going straight - no need to change direction
    } else if (top_element < 0) {
        // turn left
        turn_left(thread);
    } else {
        turn_right(thread);
    }
}

void turn_left(Thread thread) {

    if (thread.current_direction = Thread::UP) {
        thread.current_direction = Thread::LEFT;
    } else if (thread.current_direction = Thread::DOWN) {
        thread.current_direction = Thread::RIGHT;
    } else if (thread.current_direction = Thread::LEFT) {
        thread.current_direction = Thread::DOWN;
    } else { // current direction is rightwards
        thread.current_direction = Thread::UP;
    }

}

void turn_right(Thread thread) {

   if (thread.current_direction = Thread::UP) {
        thread.current_direction = Thread::RIGHT;
    } else if (thread.current_direction = Thread::DOWN) {
        thread.current_direction = Thread::LEFT;
    } else if (thread.current_direction = Thread::LEFT) {
        thread.current_direction = Thread::UP;
    } else { // current direction is rightwards
        thread.current_direction = Thread::DOWN;
    }

}

void turn_back(Thread thread) {

   if (thread.current_direction = Thread::UP) {
        thread.current_direction = Thread::DOWN;
    } else if (thread.current_direction = Thread::DOWN) {
        thread.current_direction = Thread::UP;
    } else if (thread.current_direction = Thread::LEFT) {
        thread.current_direction = Thread::RIGHT;
    } else { // current direction is rightwards
        thread.current_direction = Thread::LEFT;
    }

}

// checks whether there is a wall in current travel direction
// neighbours is [left, right, up, down]
bool wall_ahead(bool neighbours[], Thread thread) {
    switch(thread.current_direction) {
        case Thread::LEFT:
            return !neighbours[0];
        case Thread::RIGHT:
            return !neighbours[1];
        case Thread::UP:
            return !neighbours[2];
        case Thread::DOWN:
            return !neighbours[3];
        default:
            break;
    }
}

// check whether there is a neighbour in the current travel direction
bool came_from(bool neighbours[], Thread thread) {
    return !wall_ahead(neighbours, thread);
}

bool go_other_direction(bool neighbours[], Thread thread) {
    switch(thread.current_direction) {
        case Thread::LEFT: {
            for (int i = 0; i < 4; i++) {
                if (neighbours[i] && i != Thread::LEFT) {
                    thread.current_direction = i;
                }
            }
            break;
        }
        case Thread::RIGHT: {
            for (int i = 0; i < 4; i++) {
                if (neighbours[i] && i != Thread::RIGHT) {
                    thread.current_direction = i;
                }
            }
            break;
        }
        case Thread::UP: {
            for (int i = 0; i < 4; i++) {
                if (neighbours[i] && i != Thread::UP) {
                    thread.current_direction = i;
                }
            }
            break;
        }
        case Thread::DOWN: {
            for (int i = 0; i < 4; i++) {
                if (neighbours[i] && i != Thread::DOWN) {
                    thread.current_direction = i;
                }
            }
            break;
        }
        default:
            break;
    }
}

