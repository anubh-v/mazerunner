bool is_instruction(char possible_inst) {

   switch(possible_inst) {
       case '_':
       case '0':
       case '1':
       case '2':
       case '3':
       case '4':
       case '5':
       case '6':
       case '7':
       case '8':
       case '9':
       case ')':
       case '(':
       case '+':
       case '-':
       case '*':
       case '/':
       case '%':
       case '`':
       case '&':
       case '|':
       case '$':
       case '~':
       case ':':
       case ';':
       case '}':
       case '{':
       case '=':
       case '#':
       case ',':
       case '?':
       case '.':
       case '!':
       case '\\':
       case '<':
       case '>':
       case '^':
       case 'v':
           return true;
       default:
           return false;
   }

}
