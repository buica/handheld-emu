#include "../include/cart.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>


/*
 * @brief Loads a ROM file into memory.
 *
 * @param filepath The path to the ROM file.
 * @return A vector containing the ROM data.
 */
bool Cart::load(const std::string& filepath) {
    Cart m_cart;
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
    // file.read expects char * so need to cast byte data in uint8_t* to char*
    if (!file.read(reinterpret_cast<char*>(m_rom_data.data()), size)) {
        std::cerr << "Failed to read ROM file: " << filepath << std::endl;
        return false;
    }

    return true;
}

