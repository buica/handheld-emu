#pragma once

#include "common.hpp"
#include "cart.hpp"
#include "io_registers.hpp"
#include <array>

// Memory class will act as our emulator's memory bus and
// bus controller, handling memory access and communication between the CPU and PPU.
//

// TO-DO:
// - [x] implement memory mapping
// - [x] implement basic memory operations
// - [x] work more on loadRom()
// - [] stub out i/o range methods and start thinking about future integration with i/o.
//      maybe switch cases for each i/o address
// LATER: we should probably create a SERIAL class to optimize serial communication to/from peripherals.

constexpr u32 DMG_ADDRESS_SPACE_SIZE = 0x10000; // Gameboy total addressable space = 64KiB
constexpr u16 SERIAL_TRANSFER_DATA = 0xFF01;
constexpr u16 SERIAL_TRANSFER_CONTROL = 0xFF02;

constexpr u16 ROM_BANK_00_START = 0x0000;
constexpr u16 ROM_BANK_00_END = 0x3FFF;
constexpr u16 ROM_BANK_NN_START = 0x4000;
constexpr u16 ROM_BANK_NN_END = 0x7FFF;
constexpr u16 VRAM_START = 0x8000;
constexpr u16 VRAM_END = 0x9FFF;
constexpr u16 EXT_RAM_START = 0xA000;
constexpr u16 EXT_RAM_END = 0xBFFF;
// Work ram divided into 2 regions as pan doc notes the following
// for the D000-DFFF region: "in CGB mode, switchable bank 1-7".
// we're sticking with 1 region for now.
constexpr u16 WRAM_START = 0xC000;
constexpr u16 WRAM_END = 0xDFFF;
constexpr u16 ECHO_RAM_START = 0xE000;
constexpr u16 ECHO_RAM_END = 0xFDFF;
constexpr u16 OAM_START = 0xFE00;
constexpr u16 OAM_END = 0xFE9F;
constexpr u16 UNUSED_START = 0xFEA0;
constexpr u16 UNUSED_END = 0xFEFF;
constexpr u16 IO_START = 0xFF00;
constexpr u16 IO_END = 0xFF7F;
constexpr u16 HRAM_START = 0xFF80;
constexpr u16 HRAM_END = 0xFFFE;
constexpr u16 INTERRUPT_ENABLE = 0xFFFF;

constexpr u16 WRAM_SIZE = WRAM_END - WRAM_START + 1; // 0x2000
constexpr u16 ECHO_RAM_SIZE = ECHO_RAM_END - ECHO_RAM_START + 1; // 0x1E00
constexpr u8 HRAM_SIZE = HRAM_END - HRAM_START + 1; // 0x7F


class Memory {
public:
    Memory(Cart& cart, IORegisters& ioRegister);
    u8 readByte(u16 address);
    u16 readWord(u16 address);
    void writeByte(u16 address, u8 value);

private:
    std::array<u8, WRAM_SIZE> m_wram;
    std::array<u8, ECHO_RAM_SIZE> m_echo_ram;
    std::array<u8, HRAM_SIZE> m_hram;
    u8* m_interrupt_enable;

    Cart& m_cart;
    IORegisters& m_ioRegister;

    void initMemory();
};
