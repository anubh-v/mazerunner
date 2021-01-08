#include "thread.h"
#include <queue>
#include "instruction_dispatcher.h"

using namespace std;

void set_starting_pointer(Thread thread, char** program);

void run_single_instruction(char** program, Thread thread);

//void update_direction(char** program, Thread thread);

void interpret(char** program) {

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
void set_starting_pointer(Thread thread, char** program) {
    
}

void run_single_instruction(char** program, Thread thread) {
    thread.move_to_next_inst();
   
    int x = thread.program_pointer[0];
    int y = thread.program_pointer[1];
    char instruction = program[x][y];
    eval_instruction(instruction, thread);

    // update_direction(program, thread);

}


