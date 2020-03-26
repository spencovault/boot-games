#include "defines.h"

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




// Prints a single character to the terminal (for testing)
char print_keystroke(char outchar, unsigned short int attr)
{
    __asm__("int $0x10"
            :
            : "a" ((0x0e << 8) | outchar), "b" (attr));
}

// Testing done in main()
void main(void) {

    unsigned short int input;

    while(1)
    {
        input = get_keystroke_ascii();

        if (input == 'A')
        {
            // If the scan code entered is equal to the value of LARROW_RELEASE
            // Print the letter G to quemu
            print_keystroke('G', 0);
        }
        else
        {
            print_keystroke(0x00, 0);
        }    
    }
    

    while (1) {
        __asm__ ("hlt");
    };
}