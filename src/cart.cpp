#include "../include/cart.hpp"
#include <iostream>
#include <vector>
#include <fstream>



void loadRom(const std::string& filepath) {
    // assert file is .gb
    // load rom data into array/vector
    //
    std::vector<u8> romData;
    std::ifstream file(filepath, std::ios::binary); //open in binary mode to get raw bytes
    if (!file.is_open()) {
        std::cerr << "Failed to open ROM file: " << filepath << std::endl;
    }

}
