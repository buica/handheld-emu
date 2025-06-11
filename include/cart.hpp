#ifndef CART_HPP
#define CART_HPP

#include "common.hpp"
#include <string>

// To-Do
// - [ ] Implement loadRom function
// - [ ] boot up one of blargg's test rom
//
class Cart
{
private:
    // cartridge headers (check out pan docs for full info)
    // header located at address range $0100 - $014F
    struct RomHeader
    {
        u8 entry[4]; // $0100-$0103
        u8 logo[0x30]; // $0104-$0133
        char title[16]; // $0134-$0143
        u8 newLicenseeCode; // $0144-$0145
        u8 sgbFlag; // $0146
        u8 cartType; // $0147
        u8 romSize; // $0148
        u8 ramSize; // $0149
        u8 destCode; // $014A
        u8 licenseeCode; // $014B, $33 means use new code
        u8 romVersion; // $014C
        u8 checksum; // $014D
        u8 globalChecksum; // $014E-014F
    };

public:
    void loadRom(const std::string& filepath);
};

#endif
