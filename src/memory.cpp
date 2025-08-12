#include "../include/memory.hpp"
#include "../include/cart.hpp"
#include <iostream>



Memory::Memory(Cart& cart, IORegisters& ioRegister) : m_cart(cart), m_ioRegister(ioRegister) {

}

// TODO
// - [] implement serial data transfer ports
// - [] finish correct behavior for each address range
//
// Read byte from memory at given address
// Use pan docs memory map for behavior

 /*
  * @brief Reads a byte from memory at the given address.
  * @param address The address to read from.
  * @return The byte read from memory.
  */
u8 Memory::readByte(u16 address) {
    if (address >= ROM_BANK_00_START && address <= ROM_BANK_00_END) {
        // 16 KiB ROM bank 00
        return m_cart.readByte(address);

    } else if (address >= ROM_BANK_NN_START && address <= ROM_BANK_NN_END) {

    } else if (address >= VRAM_START && address <= VRAM_END) {
        // 8 KiB Video RAM
    } else if (address >= EXT_RAM_START && address <= EXT_RAM_END) {
        // 8 KiB External RAM
    } else if (address >= WRAM_START && address <= WRAM_END) {
        // 8 KiB work RAM
    } else if (address >= ECHO_RAM_START && address <= ECHO_RAM_END) {
        // 8 KiB echo RAM
    } else if (address >= OAM_START && address <= OAM_END) {
        // Object attribute memory (OAM)
    } else if (address >= UNUSED_START && address <= UNUSED_END) {
        // Unused memory. Returns 0s and does nothing.
        return 0x00;
    } else if (address >= IO_START && address <= IO_END) {
        // i/o registers
        // look at i/o ranges
        // to-do: use switch statements to handle corresponding regs
    } else if (address >= HRAM_START && address <= HRAM_END) {
        // high RAM
    } else if (address == INTERRUPT_ENABLE) {
        // interrupt enable register (IE)
    } else {
        std::cerr << "Invalid memory address: 0x" << std::hex << std::uppercase << address << std::endl;
        return 0xFF; // unmapped memory
    }
}

/*
 * @brief Reads a 16-bit value from memory at the given address.
 * @param address The address to read from.
 * @return The 16-bit value read from memory in little endian format.
 */
u16 Memory::readWord(u16 address) {
    u8 low = readByte(address);
    u8 high = readByte(address + 1); // Little Endian
    return (high << 8) | low;
}

/*
 * @brief Writes a byte to memory at the given address.
 * @param address The address to write to.
 * @return void
 */
void Memory::writeByte(u16 address, u8 value) {
    if (address >= ROM_BANK_00_START && address <= ROM_BANK_00_END) {
        // 16 KiB ROM bank 00

    } else if (address >= ROM_BANK_NN_START && address <= ROM_BANK_NN_END) {

    } else if (address >= VRAM_START && address <= VRAM_END) {
        // 8 KiB Video RAM
    } else if (address >= EXT_RAM_START && address <= EXT_RAM_END) {
        // 8 KiB External RAM
    } else if (address >= WRAM_START && address <= WRAM_END) {
        // 8 KiB work RAM
    } else if (address >= ECHO_RAM_START && address <= ECHO_RAM_END) {
        // 8 KiB echo RAM
    } else if (address >= OAM_START && address <= OAM_END) {
        // Object attribute memory (OAM)
    } else if (address >= UNUSED_START && address <= UNUSED_END) {
        // Unused memory. Returns 0s and does nothing.

    } else if (address >= IO_START && address <= IO_END) {
        // i/o registers
        // look at i/o ranges
        // to-do: use switch statements to handle corresponding regs
    } else if (address >= HRAM_START && address <= HRAM_END) {
        // high RAM
    } else if (address == INTERRUPT_ENABLE) {
        // interrupt enable register (IE)
    } else {
        std::cerr << "Invalid memory address: 0x" << std::hex << std::uppercase << address << std::endl;
    }
}
