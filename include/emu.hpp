#ifndef EMU_HPP
#define EMU_HPP

#include "common.hpp"

// contains data of running emulator
struct EmuContext
{
    bool paused;
    bool running;
    u64 ticks;
};

int emuRun(int argc, int **argv);

EmuContext *getContext();

#endif