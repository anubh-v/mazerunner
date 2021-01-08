#include "thread.h"
#include <queue>

using namespace std;

void set_starting_pointer(Thread thread, char** program);

void run_single_instruction(char** program, Thread thread);

void interpret(char** program) {

    // setup a queue of threads (empty for now)
    queue<Thread> runnable_threads;

    // setup first thread
    Thread root_thread;
    set_starting_pointer(root_thread, program);
    queue.push(runnable_threads);

    while(true) {
        // get thread to run
        Thread current_thread = runnable_threads.pop();

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
}


