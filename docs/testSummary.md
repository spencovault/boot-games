# Test Summary

Due to the low level nature of our development, we were unable to find a convenient way of unit testing the code. We did most of
our testing manually. Below details the results of our testing:

## Input

In our `input.c` code, we implemented a way for the developer to grab input from the user. Our testing method was simple:
 - Call each of the functions implemented
 - Make sure the expected results match the actual results.
 
 Each function tested in this file was tested using the above approach and was marked as passing when input was retrieved
 successfully.
 
 
 ## Graphics
 
 
 ## Random
 
 ## Player & Scoring
 
 ## Game Implentation
 
 Below is the test results for the game implentation of our development library
 
 ### Menu
 The Menu consisted of game menu elements of our spinoff of snake.io.
 
We had immediate issues with drwaing our buttons to the screen. In testing the `graphics.c` code, everything worked perfectly. And still does. But when `main.c` is compiled and linked with our game development libraries, such as `graphics`, we were greeted with unexpected results.

~~~~
// button.c

struct Button {
    char * text;
    int x_pos;
    int y_pos;
    void (*handler)();
    int is_selected;
    int color;
    int selected_color;
};
~~~~

~~~~
// button.c

void show_button(struct Button button)
{
    char * button_title = button.text;

    set_cursor_pos(button.x_pos, button.y_pos);

    while(*button_title != '\0')
    {
        write_char(*button_title, button.color);
        button_title++;
    }

}
~~~~

When trying to draw a button to the screen using the `show_button()` function from `button.c`, the button was sucessfully drawn to the screen. However, the button was not drawn to the correct position on the screen. However, the above `show_button()` does not work when the struct Button argument is a pointer. It displays the text to the screen in both cases, however in the case that its a pointer, it will not put it to the right spot on the screen. Always (0,0). But when its a local copy, it will display it to the screen in the right spot, but ONLY if we call the set_cursor_pos() BEFORE we make the call to show_button(). Having the call to set_cursor_pos() inside of the function call does not ever work.

This behavior has not been fully understood and remains a problem.
