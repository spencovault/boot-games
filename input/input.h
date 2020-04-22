/**
    @file input.h

    @brief Includes functions that can retrieve input from the user
    as well as validate this input.

    @author Brett Salyer
    

*/

#include "defines.h"

/**
 * Waits for user input and returns the input
 * as an ASCII character
 */
char get_keystroke_ascii();

/**
 * Waits for the user input and returns the input
 * as a scancode. This is used for capturing keystrokes 
 * that are not representable with an ASCII character.
 * 
 */
char get_keystroke_scancode();

/**
 * Compares the input the user has entered with
 * some other character, whether that be ASCII
 * or scan code. 
 * 
 * @param input the input the user as entered
 * @param comparing the scan code or ASCII character that you wish to check for
 */
int check_input(char input, char comparing);
