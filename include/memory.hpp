#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "common.hpp"
#include <array>

// Memory class will act as our emulator's memory bus and
// bus controller, handling memory access and communication between the CPU and PPU.
//

//To-do:
// - implement memory mapping
// - implement basic memory operations
// LATER: we should probably create a SERIAL class to optimize serial communication to/from peripherals.

constexpr u32 DMG_ADDRESS_SPACE_SIZE = 0x10000; // Gameboy total addressable space = 64KiB


class Memory {
private:
    //u8 dmgMemory[DMG_ADDRESS_SPACE_SIZE];
    std::array<u8, DMG_ADDRESS_SPACE_SIZE> dmgMemory; // will hold all our gameboy's addressable memory space
public:
    Memory();
    u8 readByte(u16 address);
    u16 readWord(u16 address);
    void writeByte(u16 address, u8 value);
    void loadRom(const std::string& filepath);
};


#endif
