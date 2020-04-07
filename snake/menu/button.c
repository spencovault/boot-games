#include "button.h"

void button_init(struct Button * button, char * text, int x, int y, void (*handler)()) {
    button->text = text;
    button->x_pos = x;
    button->y_pos = y;
    button->handler = handler;
    button->is_selected = 0;
}

