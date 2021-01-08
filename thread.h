#include <string>
#include <stack>

class Thread {

    std::string current_direction = "right";
    int program_pointer[2];
    std::stack<int> stack;

};
