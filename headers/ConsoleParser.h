#ifndef CONSOLE_PARSER_H_
#define CONSOLE_PARSER_H_

#include <stdio.h>

#include "CustomAssert.h"
#include "Logger.h"

const size_t MAX_FLAG_NAME_LENGTH = 20;
const size_t MAX_FLAG_COUNT = 40;

typedef void flag_function_t (char **arguments);

struct CONSOLE_FLAG{
    char short_name [MAX_FLAG_NAME_LENGTH];
    char long_name  [MAX_FLAG_NAME_LENGTH];

    flag_function_t *flag_function;
    size_t arguments_count;
};


int parse_flags (int argc, char **argv);
void register_flag (char short_name[], char long_name[], flag_function_t *flag_function, size_t arguments_count);
CONSOLE_FLAG *search_flag (char *flag);
int init_flags ();
void close_flags ();

#endif
