#include "../include/memory.hpp"
#include <iostream>
#include <fstream>


Memory::Memory() {
    // Initialize memory here

}

// WIP
// Read byte from memory at given address
// Use pan docs memory map for behavior
u8 Memory::readByte(u16 address) {
    if (address >= 0x0000 && address <= 0x3FFF) {
        // 16 KiB ROM bank 00
        return dmgMemory[address]; // from cart, usually fixed bank
    }
    else if (address >= 0x4000 && address <= 0x7FFF) {
        // 16 KiB ROM bank 01-NN
        return dmgMemory[address]; // from cart, switchable bank via mapper
    }
    else if (address >= 0x8000 && address <= 0x9FFF) {
        // 8 KiB Video RAM
        return dmgMemory[address];
    }
    else if (address >= 0xA000 && address <= 0xBFFF) {
        // 8 KiB External RAM
        return dmgMemory[address];
    }
    else if (address >= 0xC000 && address <= 0xCFFF) {
        // 8 KiB work RAM
        return dmgMemory[address];
    }
    else if (address >= 0xD000 && address <= 0xDFFF) {
        // 8 KiB work RAM
        return dmgMemory[address];
    }
    else if (address >= 0xE000 && address <= 0xFDFF) {
        // 8 KiB echo RAM
        return dmgMemory[address]; // to-do: mirror of WRAM
    }
    else if (address >= 0xFE00 && address <= 0xFE9F) {
        // Object attribute memory (OAM)
        return dmgMemory[address];
    }
    else if (address >= 0xFF00 && address <= 0xFF7F) {
        // i/o registers
        // look at i/o ranges
        // to-do: use switch statements to handle corresponding regs
        return dmgMemory[address];
    }
    else if (address >= 0xFF80 && address <= 0xFFFE) {
        // high RAM
        return dmgMemory[address];
    }
    else if (address >= 0xFFFF && address <= 0xFFFF) {
        // interrupt enable register (IE)
        return dmgMemory[address];
    }
    else {
        std::cerr << "Invalid memory address: 0x" << std::hex << std::uppercase << address << std::endl;
        return 0xFF; // unmapped memory
    }
}

// Return 16bit value from memory at given address where
u16 Memory::readWord(u16 address) {
    u8 low = readByte(address);
    u8 high = readByte(address + 1); // Little Endian
    return (high << 8) | low;
}

// Write byte to memory at given address
void Memory::writeByte(u16 address, u8 value) {
    if (address >= 0x0000 && address <= 0x3FFF) {
        // 16 KiB ROM bank 00
        dmgMemory[address] = value; // from cart, usually fixed bank
    }
    else if (address >= 0x4000 && address <= 0x7FFF) {
        // 16 KiB ROM bank 01-NN
        dmgMemory[address] = value;
    }
    else if (address >= 0x8000 && address <= 0x9FFF) {
        // 8 KiB Video RAM
        dmgMemory[address] = value;
    }
    else if (address >= 0xA000 && address <= 0xBFFF) {
        // 8 KiB External RAM
        dmgMemory[address] = value;
    }
    else if (address >= 0xC000 && address <= 0xCFFF) {
        // 8 KiB work RAM
        dmgMemory[address] = value;
    }
    else if (address >= 0xD000 && address <= 0xDFFF) {
        // 8 KiB work RAM
        dmgMemory[address] = value;
    }
    else if (address >= 0xE000 && address <= 0xFDFF) {
        // 8 KiB echo RAM
        dmgMemory[address] = value; // to-do: mirror of WRAM
    }
    else if (address >= 0xFE00 && address <= 0xFE9F) {
        // Object attribute memory (OAM)
        dmgMemory[address] = value;
    }
    else if (address >= 0xFF00 && address <= 0xFF7F) {
        // i/o registers
        // look at i/o ranges
        // to-do: use switch statements to handle corresponding regs
        dmgMemory[address] = value;
    }
    else if (address >= 0xFF80 && address <= 0xFFFE) {
        // high RAM
        dmgMemory[address] = value;
    }
    else if (address >= 0xFFFF && address <= 0xFFFF) {
        // interrupt enable register (IE)
        dmgMemory[address] = value;
    }
    else {
        std::cerr << "Invalid memory address: " << std::hex << address << std::endl;
    }
}
