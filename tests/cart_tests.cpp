#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <vector>

#include "../include/cart.hpp"

TEST_CASE("Test: Cart Functions") {
    // create and populate dummy ROM
    const char* test_rom_path = "test_cart.gb";
    std::vector<u8> test_rom_data = {0x00, 0x01, 0x10} // NOP; LD BC, n16; STOP

    std::ofstream output_file(test_rom_path, std::ios::binary);
    output_file.write(reinterpret_cast<const char*>(test_rom_data.data()), test_rom_data.size());
    output_file.close();

    Cart cart;

    SECTION("Test: Cart Load ROM") {
        REQUIRE(cart.load("path/to/rom/file") == true);
    }

}