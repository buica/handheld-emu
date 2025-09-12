#include "../include/cart.hpp"
#include "../include/memory.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>


/**
 * @brief Loads a ROM file into memory.
 * @param filepath The path to the ROM file.
 * @return True if load succeeds.
 */
bool Cart::load(const std::string& filepath) {
    u64 size = 0;
    try {
        size = std::filesystem::file_size(filepath);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Failed to get file size: " << e.what() << std::endl;
        return false;
    }

    std::ifstream file(filepath, std::ios::binary); //open in binary mode to get raw bytes
    if (!file.is_open()) {
        std::cerr << "Failed to open ROM file: " << filepath << std::endl;
        return false;
    }

    m_rom_data.resize(size);
    // file.read expects char * so need to cast the byte data in uint8_t* to char*
    if (!file.read(reinterpret_cast<char*>(m_rom_data.data()), size)) {
        std::cerr << "Failed to read ROM file: " << filepath << std::endl;
        return false;
    }

    return true;
}


/**
* @brief returns ROM data loaded in memory
* @return the ROM data vector
*/
std::vector<u8>& Cart::getRomData() {
    return m_rom_data;
}


/**
* @brief Read a byte from the cartridge address space, and route the read to
* ROM bank 00, switchable ROM banks, or external RAM depending on the address.
* @param address The address from cartridge space to read from
* @return The byte read from the cartridge.
*/
u8 Cart::readByte(u16 address) {
    if (address >= ROM_BANK_00_START && address <= ROM_BANK_00_END) {
        // 16 KiB ROM bank 00 (fixed)
        return m_rom_data[address];
    } else if (address >= ROM_BANK_NN_START && address <= ROM_BANK_NN_END) {
        // 16 KiB switchable ROM bank
        // for now, just read from next 16KiB block
        return m_rom_data[address];
    } else if (address >= EXT_RAM_START && address <= EXT_RAM_END) {
        // 8 KiB External RAM
        // to-do: implement external RAM banking
        return 0xFF;
    } else {
        std::cerr << "Cartridge read from invalid address: 0x" << std::hex << address << std::endl;
    }
}