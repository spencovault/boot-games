#include "button.h"

void button_init(struct Button * button, char * text, int x, int y, void (*handler)()) {
    button->text = text;
    button->x_pos = x;
    button->y_pos = y;
    button->handler = handler;
    button->is_selected = 0;
}

void button_set_x_pos(struct Button * button, int x) {
    button->x_pos = x;
}

void button_set_y_pos(struct Button * button, int y) {
    button->y_pos = y;
}

void button_set_pos(struct Button * button, int x, int y) {
    button->x_pos = x;
    button->y_pos = y;
}