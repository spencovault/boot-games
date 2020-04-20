/**
    @file input.h
    @author Brett Salyer

    @brief A library for handling input from the user via keyboard
        and as well as validating it.

*/

#include "defines.h"
#include "input.h"

// Gets a single keystroke from the user. Returns as a scancode
char get_keystroke_ascii()
{
    // A 16 bit unsigned integer for storing the 
    // Least significant 16-bits of register EAX (AH & AL)
    unsigned short int input_char;

    __asm__("int $0x16"
            : "=a" (input_char)
            : "0" (0x0));

    return ((char)input_char);
}

// Gets a single keystroke from the user. Returns an ASCII value.
char get_keystroke_scancode()
{
    // A 16 bit unsigned integer for storing the 
    // Least significant 16-bits of register EAX (AH & AL)
    unsigned short int input_char;

    __asm__("int $0x16"
            : "=a" (input_char)
            : "0" (0x0));

    return ((char) (input_char >> 8));
}

// Checks the input keyboard value and compares it to another
int check_input(char input, char comparing)
{
    if (input == comparing)
    {
        return 1;
    }else{
        return 0;
    }
}

// Assigns a function handler for when a certain input matches a key value
void on_keypress(char input, char key, void (*f)())
{
    if (check_input(input, key))
    {
        f();
    }
}

// [DEBUG] Prints a single character to the terminal (for testing)
void print_keystroke(char outchar, unsigned short int attr)
{
    __asm__("int $0x10"
            :
            : "a" ((0x0e << 8) | outchar), "b" (attr));
}

