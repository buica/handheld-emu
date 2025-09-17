#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <vector>

#include "../include/cart.hpp"

TEST_CASE("Test: Cart Functions") {
    // create and populate dummy ROM
    const char* test_rom_path = "test_cart.gb";
    const char* non_existing_rom_path = "non_existing_cart.gb";
    std::vector<u8> test_rom_data = {0x00, 0x01, 0x10}; // NOP; LD BC, n16; STOP

    std::ofstream output_file(test_rom_path, std::ios::binary);
    output_file.write(reinterpret_cast<const char*>(test_rom_data.data()), test_rom_data.size());
    output_file.close();

    Cart cart;

    SECTION("Test: Cart Load ROM Suceeds") {
        REQUIRE(cart.load(test_rom_path) == true);
    }
    SECTION("Test: Cart Load ROM Fails") {
        REQUIRE(cart.load(non_existing_rom_path) == false);
    }

    SECTION("Test: Get ROM Data from Cart") {
        REQUIRE(cart.load(test_rom_path) == true);
        auto& rom = cart.getRomData();
        REQUIRE(rom == test_rom_data);
    }

    SECTION("Test: Read Byte from ROM Bank 00") {
        REQUIRE(cart.load(test_rom_path) == true);
        REQUIRE(cart.readByte(0x0000) == 0x00); // NOP
        REQUIRE(cart.readByte(0x0001) == 0x01); // LD BC, n16
        REQUIRE(cart.readByte(0x0002) == 0x10); // STOP
        REQUIRE(cart.readByte(0x0003) == 0xFF); // out of bounds, should return 0xFF
    }

    std::remove("test_cart.gb");

}