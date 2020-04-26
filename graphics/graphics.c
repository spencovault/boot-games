#include "graphics.h"

/**
 * This sets the VGA video mode with the given video mode code.
 * 
 * @param mode The video mode code to put into the AL register, refer to:
 *             http://muruganad.com/8086/interrupt%20list/int%2010%20video%20interrupt/Int-10-AH-00-Set-Video-Mode.html
 */
void set_video_mode(u8 mode)
{
    __asm__(
        "int $0x10" : : "a" ((0x00 << 8) | mode)                        
    );
}

/**
 * Clears the screen with the default video mode, 0x0D
 */
void clear_screen()
{
    set_video_mode(0x0D);
}

/**
 * Sets the text cursor position on the screen.
 * 
 * @param x The column position of the cursor.
 * @param y The row position of the cursor.
 */
void set_cursor_pos(u8 x, u8 y)
{
    __asm__(
        "int $0x10" : : "a" (0x02 << 8),
                        "d" ((y << 8) | x)
    );
}

/**
 * Sets the background color for the entire screen.
 * 
 * @param color The color code corresponding to any of the codes defined
 *              in graphics.h
 */
void set_bg_color(u8 color)
{
    __asm__(
        "int $0x10" : : "a" (0x0b << 8),
                        "b" (color)
    );
}

/** 
 * Writes the given character to the current cursor position with the given
 * color.
 *
 * @param character The symbol to write to the screen.
 * @param color The color to render the symbol in.
 */
void write_char(u8 character, u8 color)
{
    __asm__(
        "int $0x10" : : "a" ((0x0e << 8) | character),
                        "b" (color)
    );
}

/**
 * Writes the given null-terminated string to the current cursor position with
 * the given color.
 *
 * @param str The null-terminated string to be printed.
 * @param color The color to render the string in.
 */
void write_str(char* str, u8 color)
{
    // walk through string until we reach null character
    while(*str != '\0')
    {
        write_char(*str, color);
        str++;
    }
}

/**
 * Draws a horizontal line from left to right across the screen in the given
 * color.
 *
 * @param x_pos The starting column position.
 * @param y_pos The starting row position.
 * @param end_x The ending column position.
 * @param sym The symbol to draw across the line.
 * @param color The color to render the line in.
 */
void draw_line_x(u8 x_pos, u8 y_pos, u8 end_x, u8 sym, u8 color)
{
    // since all will be on the same line, only need to set_cursor_pos once
    set_cursor_pos(x_pos, y_pos);
    for(; x_pos < end_x; x_pos++)
    {
        write_char(sym, color);
    }
}


/**
 * Draws a vertical line down the screen in the given color.
 *
 * @param x_pos The starting column position.
 * @param y_pos The starting row position.
 * @param end_y The ending row position.
 * @param sym The symbol to draw across the line.
 * @param color The color to render the line in.
 */
void draw_line_y(u8 x_pos, u8 y_pos, u8 end_y, u8 sym, u8 color)
{
    // need to set_cursor_pos because we're walking vertically downward
    for(; y_pos < end_y; y_pos++)
    {
        set_cursor_pos(x_pos, y_pos);
        write_char(sym, color);
    }
}

/**
 * Draws an optionally bordered and filled box on the screen at the given
 * coordinates.
 *
 * @param x_pos The top-left column coordinate of the box.
 * @param y_pos The top-left row coordinate of the box.
 * @param w The width of the box spanning the columns.
 * @param h The height of the box spanning the rows.
 * @param color The color to render the box in.
 * @param draw_mode A bitflag defining what type of box to draw, defined in
 *                  graphics.h. A value of 0 will display nothing. A value
 *                  of (BOX_FILL | BOX_BORDER) will render a filled and
 *                  bordered box.
 */
void draw_box(u8 x_pos, u8 y_pos, u8 w, u8 h, u8 color, int draw_mode)
{
    if(!draw_mode) // if no draw mode was specified, skip immediately
    {
        return;
    }

    u8 end_x = x_pos+w-1;
    u8 end_y = y_pos+h-1;
    
    u8 y;
    for(y = y_pos; y <= end_y; y++)
    {
        // starting a new line in the box
        set_cursor_pos(x_pos, y);
        u8 x;
        for(x = x_pos; x <= end_x; x++)
        {
            if(draw_mode & BOX_BORDER)
            {
                if(x == end_x && y == end_y) // bottom right
                {
                    write_char(188, color);
                }
                else if(x == x_pos && y == end_y) // bottom left
                {
                    write_char(200, color);
                }
                else if(x == end_x && y == y_pos) // top right
                {
                    write_char(187, color);
                }
                else if(x == x_pos && y == y_pos) // top left
                {
                    write_char(201, color);
                }
                else if(x == x_pos || x == end_x) // vertical lines
                {
                    write_char(186, color);
                }
                else if(y == y_pos || y == end_y) // horizontal lines
                {
                    write_char(205, color);
                }
                else if(draw_mode & BOX_FILL) // fill
                {
                    write_char(178, color);
                }
                else // no fill, just moving cursor forward
                {
                    set_cursor_pos(x+1, y);
                }
            }
            else if(draw_mode & BOX_FILL)// fill all if no border
            {
                write_char(178, color);
            }
        }
    }
}

/**
 * This will draw a test region to the screen at the given position.
 *
 * @param x_pos The top-left column coordinate of the region.
 * @param y_pos The top-left row coordinate of the region.
 * @param w The width of the region spanning the columns.
 * @param h The height of the region spanning the rows.
 */
void test_render(u8 x_pos, u8 y_pos, u8 w, u8 h)
{
    u8 end_x = x_pos+w;
    u8 end_y = y_pos+h;

    u8 y;
    u8 color = 0;
    for(y = y_pos; y < end_y; y++)
    {
        set_cursor_pos(x_pos, y);
        u8 x;
        for(x = x_pos; x < end_x; x++)
        {
            write_char(233, color);
            color = (color+1)%16;
        }
    }
}
