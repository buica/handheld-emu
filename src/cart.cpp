#include "../include/cart.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>


//
std::vector<u8> loadRom(const std::string& filepath) {
    // reports error if file doesnt exist so lets use this for error handling
    u64 size = 0;
    try {
        size = std::filesystem::file_size(filepath);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Failed to get file size: " << e.what() << std::endl;
        return {};
    }

    std::ifstream file(filepath, std::ios::binary); //open in binary mode to get raw bytes
    if (!file.is_open()) {
        std::cerr << "Failed to open ROM file: " << filepath << std::endl;
        return {};
    }

    std::vector<u8> romData(size);
    // file.read expects char * so need to cast byte data in uint8_t* to char*
    if (!file.read(reinterpret_cast<char*>(romData.data()), size)) {
        std::cerr << "Failed to read ROM file: " << filepath << std::endl;
        return {};
    }

    return romData;
}
