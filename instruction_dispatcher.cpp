#include "instruction_dispatcher.h"

#include <stack>

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define SIZE 10

// Return 1 if the current thread of execution is complete (i.e. @ char encountered)
int eval_instruction(char instruction, Thread thread) {
  if (isdigit(instruction)) {
    int d = instruction - '0';
    int to_add = thread.main_stack.top() * 10 + d;
    thread.main_stack.push(to_add);
    return 0;
  }

  switch(instruction) {
      case '[': {
        int d = getchar();
        if (isdigit(d)) {
          int n = d - '0';
          int c = getchar();
          if (c == ']') {
            // TODO: spawn threads

            return 0;
          }
        } else if (d == ']') {
          // TODO: join

          return 0;
        }
        
        fprintf(stderr, "!!! The split syntax is '[number]' ");
        break;
      }
      case '"':
        break; 
      
      case '\'': {
        int x = thread.program_pointer[0];
        int y = thread.program_pointer[1];
        printf("Current position: (%d, %d)\n", x, y);
        break;
      }
        
        // TODO: print main stack
        // TODO: print aux stack

      case '@':
        return 1;
        
      case '_':
        thread.main_stack.push(0);
        break;
      case ')': {
        int plus_one = thread.main_stack.top() + 1;
        thread.main_stack.pop();
        thread.main_stack.push(plus_one);
        break;
      }
      case '(': {
        int minus_one = thread.main_stack.top() - 1;
        thread.main_stack.pop();
        thread.main_stack.push(minus_one);
        break;
      }
      case '+': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        int a = thread.main_stack.top();
        int sum = b + a;
        thread.main_stack.push(sum);
        break;
      }
      case '-': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        int a = thread.main_stack.top();
        int sub = a - b;
        thread.main_stack.push(sub);
        break;
      }
      
      case '*': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        int a = thread.main_stack.top();
        int product = b * a;
        thread.main_stack.push(product);
        break;
      }

      case '/': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        int a = thread.main_stack.top();
        int div = (int) a / b;
        thread.main_stack.push(div);
        break;
      }
      
      case '%': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        int a = thread.main_stack.top();
        int mod = a % b;
        thread.main_stack.push(mod);
        break;
      }

      case '`': {
        int neg = thread.main_stack.top() * -1;
        thread.main_stack.push(neg);
        break;
      }
      
      case '&': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        int a = thread.main_stack.top();
        int end = a & b;
        thread.main_stack.push(end);
        break;
      }
      
      case '|': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        int a = thread.main_stack.top();
        int end = a | b;
        thread.main_stack.push(end);
        break;
      }
      
      case '$': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        int a = thread.main_stack.top();
        int xr = a ^ b;
        thread.main_stack.push(xr);
        break;
      }

      case '~': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        int nt = ~ b;
        thread.main_stack.push(nt);
        break;
      }

      case ':': {
        int duplicate = thread.main_stack.top();
        thread.main_stack.push(duplicate);
        break;
      }

      case ';': {
        thread.main_stack.pop();
        break;
      }

      case '}': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        thread.aux_stack.push(b);
        break;
      }
      
      case '{': {
        int b = thread.aux_stack.top();
        thread.aux_stack.pop();
        thread.main_stack.push(b);
        break;
      }
      
      case '=': {
        int main = thread.main_stack.top();
        thread.main_stack.pop();

        int aux = thread.aux_stack.top();
        thread.aux_stack.pop();

        thread.aux_stack.push(main);
        thread.main_stack.push(aux);
        break;
      }
      
      case '#': {
        int depth = thread.main_stack.size();
        thread.main_stack.push(depth);
        break;
      }

      case ',': {
        int c = getchar();
        if (c == EOF) {
          thread.main_stack.push(-1);
        } else {
          thread.main_stack.push(c);
        }
        break;
      }
      
      case '?': {
        int i = 0;
        int c;
        char *number = (char *) malloc(sizeof(char) * SIZE);
        while (true) {
          c = getchar();
          if (c == '-' || c == '+' || isdigit(c)) {
            number[i] = c;
            i++;
            break;
          }
        }
        
        while ((c = getchar()) != EOF) {
          if (i > 0 && i % SIZE == 0) {
            number = (char *) realloc(number, sizeof(char) * ((i / SIZE) + 1) * SIZE);
          }
          
          if (isdigit(c)) {
            number[i] = c;
            i++;
          } else {
            fprintf(stderr, "!!! '?' should be followed by a number");
          } 
        }

        int n;
        sscanf(number, "%d", &n);
        thread.main_stack.push(n);

        thread.main_stack.push(0);
        break; 
      }

      case '.': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        int ascii = b % 256;
        putchar(ascii);
        break;
      }

      case '!': {
        int b = thread.main_stack.top();
        thread.main_stack.pop();
        break;
      }
      
      case '\\': {
        putchar('\n');
        break;
      }

      default:
        // error! unexpected instruction
        break;
  }

  return 0;
}


