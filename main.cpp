#include "mbed.h"

// main() runs in its own thread in the OS
int main()
{
    crusherSystemInit();
    
    while (true) {
        crusherSystemUpdate();
    }
}

