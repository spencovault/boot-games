int kernelmain(int argc, char **argv)
{
    // program goes here :)

    // end of program, hlt forever instead of returning since theres nothing to
    // return to
    while (1)
    {
        __asm__ ("hlt");
    };
}
