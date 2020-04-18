#include "graphics.h"

void kernelmain()
{
    set_video_mode(0x0D);

    test_render(0, 0, 10, 10);

    while(1)
    {
        __asm__("hlt");
    }
}

