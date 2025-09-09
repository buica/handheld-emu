#pragma once


#include "common.hpp"
#include <string>
#include <vector>

// To-Do
// - [x] Implement loadRom function
// - [ ] change romHeader naming to snake_case to be consistent
// - [ ] boot up one of blargg's test rom
//
class Cart {
public:
    Cart() = default;
    bool load(const std::string& filepath);
    std::vector<u8>& getRomData();
    u8 readByte(u16 address);


private:
    std::vector<u8> m_rom_data;
    // cartridge headers (check out pan docs for full info)
    // header located at address range $0100 - $014F
    struct RomHeader {
        u8 entry[4]; // $0100-$0103
        u8 logo[0x30]; // $0104-$0133
        char title[16]; // $0134-$0143
        u8 new_licensee_code; // $0144-$0145
        u8 sgb_flag; // $0146
        u8 cart_type; // $0147
        u8 rom_size; // $0148
        u8 ram_size; // $0149
        u8 dest_code; // $014A
        u8 licensee_code; // $014B, $33 means use new code
        u8 rom_version; // $014C
        u8 checksum; // $014D
        u8 global_checksum; // $014E-014F
    };
};
