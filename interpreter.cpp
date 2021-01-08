#include "thread.h"
#include <queue>

using namespace std;

void set_starting_pointer(Thread thread, char** program);

void interpret(char** program) {

    // setup a queue of threads (empty for now)
    queue<Thread> runnable_threads;

    // setup first thread
    Thread root_thread;
    set_starting_pointer(root_thread, program);

    // interpret program according to instructions

}

// set the initial program pointer for a program
void set_starting_pointer(Thread thread, char** program) {
    
}
