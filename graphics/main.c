#define RED    0x04
#define BROWN  0x06
#define YELLOW 0x0E
#define GREEN  0x02
#define CYAN   0x03
#define BLUE   0x01
#define PURPLE 0x05
#define GRAY   0x08
#define WHITE  0x0F

typedef unsigned char u8;

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

void main(void)
{
    // 320x200, 16 colors
    set_video_mode(0x0D);

    u8 y;
    u8 color = 0;
    for(y = 0; y < 20; y++)
    {
        u8 x;
        for(x = 0; x < 32; x++)
        {
            if((x+y+color)%3)
            {
                set_cursor_pos(x, y);
                write_char(233, color);
            }
            color = (color+1)%16;
        }
    }

    // program end
    while (1)
    {
        __asm__ ("hlt");
    };
}

