#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "common.hpp"
#include <array>

// Memory class will act as our emulator's memory bus and
// bus controller, handling memory access and communication between the CPU and PPU.
//

//To-do:
// - [x] implement memory mapping
// - [x] implement basic memory operations
// - [x] work more on loadRom()
// LATER: we should probably create a SERIAL class to optimize serial communication to/from peripherals.

constexpr u32 DMG_ADDRESS_SPACE_SIZE = 0x10000; // Gameboy total addressable space = 64KiB
constexpr u16 SERIAL_TRANSFER_DATA = 0xFF01;
constexpr u16 SERIAL_TRANSFER_CONTROL = 0xFF02;

class Memory {
private:
    //u8 dmgMemory[DMG_ADDRESS_SPACE_SIZE];
    std::array<u8, DMG_ADDRESS_SPACE_SIZE> dmgMemory; // will hold all our gameboy's addressable memory space
public:
    Memory() = default;
    u8 readByte(u16 address);
    u16 readWord(u16 address);
    void writeByte(u16 address, u8 value);
};

#endif
