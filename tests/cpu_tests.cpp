#include <catch2/catch_test_macros.hpp>

#include "../include/cpu.hpp"

TEST_CASE("Test: 8-bit Register Getters") {
    CPU cpu;
    REQUIRE(cpu.getA() == 0x00);
    REQUIRE(cpu.getB() == 0x00);
    REQUIRE(cpu.getC() == 0x00);
    REQUIRE(cpu.getD() == 0x00);
    REQUIRE(cpu.getE() == 0x00);
    REQUIRE(cpu.getF() == 0x00);
    REQUIRE(cpu.getH() == 0x00);
    REQUIRE(cpu.getL() == 0x00);
}

// void CPU::initRegisters()
TEST_CASE("Test: CPU Register Initialization") {
    CPU cpu;

    SECTION("8-bit Register Initialization") {
        REQUIRE(cpu.getA() == 0x00);
        REQUIRE(cpu.getB() == 0x00);
        REQUIRE(cpu.getC() == 0x00);
        REQUIRE(cpu.getD() == 0x00);
        REQUIRE(cpu.getE() == 0x00);
        REQUIRE(cpu.getF() == 0x00);
        REQUIRE(cpu.getH() == 0x00);
        REQUIRE(cpu.getL() == 0x00);
    }

    SECTION("16-bit Register Initialization") {
        REQUIRE(cpu.getAF() == 0x0000);
        REQUIRE(cpu.getBC() == 0x0000);
        REQUIRE(cpu.getDE() == 0x0000);
        REQUIRE(cpu.getHL() == 0x0000);
        REQUIRE(cpu.getSP() == 0x0000);
        REQUIRE(cpu.getPC() == 0x0100);
    }
}

// void CPU::printCPU()
// TEST_CASE("Test: Printing CPU Register Values for Logging") {
//     CPU cpu;
//     cpu.printCPU();

//     // test formatting of our log outputs here
// }


//