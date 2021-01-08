#include "thread.h"
#include <queue>
#include "instruction_dispatcher.h"
#include "instruction_set.h"
#include "src/parser.h"

using namespace std;

void set_starting_pointer(Thread thread, Program program);

void run_single_instruction(Program program, Thread thread);

void update_direction(Program program, Thread thread);

void interpret(Program program) {

    // setup a queue of threads (empty for now)
    queue<Thread> runnable_threads;

    // setup first thread
    Thread root_thread;
    set_starting_pointer(root_thread, program);
    runnable_threads.push(root_thread);

    while(true) {
        // get thread to run
        Thread current_thread = runnable_threads.back();
        runnable_threads.pop();

        // interpret program according to instructions
        run_single_instruction(program, current_thread);

        // suspend thread
        runnable_threads.push(current_thread);

    }
}

// set the initial program pointer for a program
void set_starting_pointer(Thread thread, Program program) {
    // find the first character that represents an instruction
    int num_rows = program.nr;
    int num_cols = num_rows; // assume same number of cols and rows
    char** grid = program.grid;

    for(int i = 0; i < num_rows; i++) {
        char* row = grid[i];
        for (int j = 0; j < num_cols; j++) {
            char current_char = row[j];
            if (is_instruction(current_char)) {
                thread.program_pointer[0] = j; // set x coord
                thread.program_pointer[1] = i; // set y coord
                return;
            }
        }
    }


   // if control reaches here, we have an error:
   // the program has no starting point. How to handle?

}

void run_single_instruction(Program program, Thread thread) {
    thread.move_to_next_inst();

    char instruction; // get current instruction

    eval_instruction(instruction, thread.stack);

    update_direction(program, thread);

}


