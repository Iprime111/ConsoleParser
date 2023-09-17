#include "ConsoleParser.h"

void help (char **arguments){
    printf ("help\n");
}

void func (char **arguments){
    printf ("arg1 = %s, arg2 = %s\n", *arguments, *(arguments + 1));
}

int main (int argc, char **argv){
    PushLog (1);

    register_flag ("-h", "--help", help, 0);
    register_flag ("-f", "--func", func, 2);

    parse_flags (argc, argv);

    RETURN 0;
}
