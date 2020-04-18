#include "graphics.h"

void set_video_mode(u8 mode)
{
    __asm__(
        "int $0x10" : : "a" ((0x00 << 8) | mode)                        
    );
}

void clear_screen()
{
    set_video_mode(0);
}

void set_cursor_pos(u8 x, u8 y)
{
    __asm__(
        "int $0x10" : : "a" (0x02 << 8),
                        "d" ((y << 8) | x)
    );
}

void set_bg_color(u8 color)
{
    __asm__(
        "int $0x10" : : "a" (0x0b << 8),
                        "b" (color)
    );
}

void write_char(u8 character, u8 color)
{
    __asm__(
        "int $0x10" : : "a" ((0x0e << 8) | character),
                        "b" (color)
    );
}

void write_str(char* str, u8 color)
{
    while(str != '\0')
    {
        write_char(*str, color);
        str++;
    }
}

void test_render(u8 x_pos, u8 y_pos, u8 w, u8 h)
{
    u8 end_x = x_pos+w;
    u8 end_y = y_pos+h;

    u8 y;
    u8 color = 0;
    for(y = y_pos; y < end_y; y++)
    {
        u8 x;
        for(x = x_pos; x < end_x; x++)
        {
            set_cursor_pos(x, y);
            write_char(233, color);
            color = (color+1)%16;
        }
    }
}

