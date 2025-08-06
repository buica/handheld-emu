#pragma once

#include "common.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "cart.hpp"
#include "ppu.hpp"


// switching from singleton, context-based architecture
// to a more flexible constructor based architecture
// This system class will 'wire' all the gameboy components together
// by passing required refs to each component (dependency injection)


class System {
public:

private:
    System();
    Cart m_cart;
    Memory m_memory;
    CPU m_cpu;
    PPU m_ppu;



};
