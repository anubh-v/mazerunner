
Mazerunner is a two dimensional programming language that supports multi-threading. It is an extension of the Labyrinth language. 
Programs are written as mazes. Control flow decisions are made at maze junctions.
New threads can also be spawned at junctions, allowing the program to explore multiple branches of the maze concurrently.

### Details
State needed for each thread:
- Position of program pointer
- Stack
- Current direction of travel

Setup of the interpreter:
- "Minimal parser" component that reads the source code character by character and stores it into a 2D matrix of chracters
- This 2D matrix is handed to the interpreter component, which will intialise the first thread and start evaluation.
- The interpreter keeps track of "runnable threads". Each thread is an object (program pointer, stack, current direction of travel)
- The interpreter runs a single instruction for each thread, and then switches threads in a round-robin manner.
