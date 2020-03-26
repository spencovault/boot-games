void main(void) {

int seconds;
int minutes;
int seed;
int random_val;
    

    __asm__("mov $0x02, %ah");  // Set interrupt to read system time
    __asm__("int $0x1A");       // Call RTC interrupt
    __asm__("mov %%dh, %%al"    // Put value of seconds into variable 'seed'
        : "=a" (seconds)
        :
    );
    __asm__("mov %%cl, %%al"
        : "=a" (minutes)     // Put the value of minutes into 'multiplier'
        :
    );

    random_val = ((minutes + 1) * seconds) % 61;

    __asm__ (
            "int $0x10" : : "a" ((0x0e << 8) | random_val)
    );
    

    while (1) {
        __asm__ ("hlt");
    };
}