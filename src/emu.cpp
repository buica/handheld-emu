#include <cstdio>
#include "include/common.hpp"
#include "include/cpu.hpp"
#include "include/cart.hpp"
#include "include/emu.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Core emulator components
//- CPU
//- Cart
//- Address Bus
//- PPU (pixel processing unit)
//- Timer

// todo
// add cart loading check + function
// initialize video + ppu
// for video: check sdl2 docs + learn how it works

static EmuContext context;

EmuContext *getContext()
{
    return &context;
}


