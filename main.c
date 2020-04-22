#include "graphics/graphics.h"

int kernelmain(int argc, char **argv)
{
    // 320x200 pixels, 16 colors
    set_video_mode(0x0D);

    // program goes here :)

    // end of program, hlt forever instead of returning since theres nothing to
    // return to
    while (1)
    {
        __asm__ ("hlt");
    };
}
