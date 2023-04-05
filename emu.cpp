#include <iostream>

#include "include/emu.hpp"
#include "include/common.hpp"

// Core emulator components
//- CPU
//- Cart
//- Address Bus
//- PPU (pixel processing unit)
//- Timer

static EmuContext context;

EmuContext *getContext()
{
    return &context;
}

int emuRun(int argc, int **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: emu <rom-file>" << std::endl;
        return -1;
    }

    // todo
    // add cart loading check + function
    // initialize video + ppu
    // for video: check sdl2 docs + learn how it works

    context.running = true;
    context.paused = false;

    // main infinite game loop
    while (context.running)
    {

    }
}