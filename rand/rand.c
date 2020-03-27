int rand(int max)
{

    int seconds;
    int minutes;
    int random_val;
    

    __asm__("mov $0x02, %ah");  // Set interrupt to read system time
    __asm__("int $0x1A");       // Call RTC interrupt
    __asm__("mov %%dh, %%al"    // Put value of seconds into variable 'seconds'
        : "=a" (seconds)
        :
    );
    __asm__("mov %%cl, %%al"
        : "=a" (minutes)     // Put the value of minutes into 'multiplier'
        :
    );

    random_val = ((minutes + 1) * seconds) % 61;    // LCG producing # between 0 and 60
    random_val = random_val % max;                  // Mod number to be inbetween 0 and max

    return random_val;
}

int rand() 
{
    int seconds;
    int minutes;
    int random_val;

    __asm__("mov $0x02, %ah");  // Set interrupt to read system time
    __asm__("int $0x1A");       // Call RTC interrupt
    __asm__("mov %%dh, %%al"    // Put value of seconds into variable 'seconds'
        : "=a" (seconds)
        :
    );
    __asm__("mov %%cl, %%al"
        : "=a" (minutes)     // Put the value of minutes into 'multiplier'
        :
    );

    random_val = ((minutes + 1) * seconds) % 61;    // LCG producing # between 0 and 60

    return random_val;
}