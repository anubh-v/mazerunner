#include <stack>
#include "thread.h"
#include "src/parser.h"
#include "instruction_set.h"

void update_direction(Program program, Thread thread) {

    // find number of neighbours
    int thread_x = thread.program_pointer[0];
    int thread_y = thread.program_pointer[1];

    int num_neighbours = 0;

    // check neighbouring squares in all 4 directions

    if (is_neighbour(thread_x + 1, thread_y, program.nr, program.nr, program.grid)) {
        num_neighbours++;
    }

    if (is_neighbour(thread_x - 1, thread_y, program.nr, program.nr, program.grid)) {
        num_neighbours++;
    }

    if (is_neighbour(thread_x, thread_y + 1, program.nr, program.nr, program.grid)) {
        num_neighbours++;
    }

    if (is_neighbour(thread_x, thread_y - 1, program.nr, program.nr, program.grid)) {
        num_neighbours++;
    }

    // apply the direction update rules, once number of neighbours is known
    switch(num_neighbours) {
        case 1:
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
