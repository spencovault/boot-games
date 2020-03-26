/**
    @file input.h

    @brief Includes functions that can retrieve input from the user
    as well as validate this input.

    @author Brett Salyer
    

*/

#include "defines.h"


char get_keystroke_ascii();
char get_keystroke_scancode();
int check_input(char input, char comparing);
