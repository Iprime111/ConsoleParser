#include "ConsoleParser.h"

static struct CONSOLE_FLAG *registered_flags = NULL;
static size_t flags_count = 0;

static int init_flags_array_ = init_flags ();

bool parse_flags (int argc, char **argv){
    PushLog (2);

    custom_assert (argv != NULL, pointer_is_null, -1);

    if (argc < 2){
        RETURN true;
    }

    struct CONSOLE_FLAG *current_flag = NULL;
    bool is_searching_flag = false;
    size_t arguments_readed = 0;
    char **current_arguments_begin = NULL;

    for (size_t argument_index = 1; argument_index < (size_t) argc; argument_index++){

        struct CONSOLE_FLAG *test_flag = NULL;
        if ((test_flag = search_flag (argv [argument_index])) != NULL){

            current_flag = test_flag;

            if (is_searching_flag){
                RETURN false;
            }

            is_searching_flag = true;
            current_arguments_begin = argv + argument_index;

            if (current_flag->arguments_count == 0){
                is_searching_flag = false;
                current_flag->flag_function (current_arguments_begin);
            }

            continue;
        }

        if (is_searching_flag){
            arguments_readed++;

            if (arguments_readed == current_flag->arguments_count){
                current_flag->flag_function (current_arguments_begin + 1);

                is_searching_flag = false;
                arguments_readed = 0;
            }
        }

    }

    RETURN true;
}

CONSOLE_FLAG *search_flag (char *flag){
    PushLog (3);

    for (size_t flag_index = 0; flag_index < flags_count; flag_index++){
        if (strcmp (registered_flags [flag_index].long_name,  flag)  == 0 ||
            strcmp (registered_flags [flag_index].short_name, flag)  == 0){

            RETURN registered_flags + flag_index;
        }
    }

    RETURN NULL;
}

bool register_flag (char short_name[], char long_name[], flag_function_t *flag_function, size_t arguments_count){
    PushLog (2);

    custom_assert (flag_function != NULL, pointer_is_null, false);
    custom_assert (short_name != NULL, pointer_is_null, false);
    custom_assert (long_name != NULL, pointer_is_null, false);
    custom_assert (long_name != short_name, not_enough_pointers, false);

    strncpy (registered_flags [flags_count].short_name, short_name, MAX_FLAG_NAME_LENGTH);
    strncpy (registered_flags [flags_count].long_name,  long_name,   MAX_FLAG_NAME_LENGTH);

    registered_flags [flags_count].flag_function = flag_function;
    registered_flags [flags_count].arguments_count = arguments_count;

    flags_count++;

    RETURN true;
}

int init_flags (){
    registered_flags = (struct CONSOLE_FLAG *) calloc (MAX_FLAG_COUNT, sizeof (CONSOLE_FLAG));
    atexit (close_flags);

    return 1;
}

void close_flags (){
    free (registered_flags);
}
