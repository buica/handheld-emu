#ifndef CPU_HPP
#define CPU_HPP

#include "common.hpp"
#include "memory.hpp"

//to do:
// read more about z80/8080 cpu architecture
// implement constants
// implement isa gradually, high priority opcodes first
// use blarg's test roms to test


class CPU {
private:
// CPU Registers
// We need to be able to access same registers as 16bit regsters and 2 separate 8bit registers
// Using unions along with grouping the 8bit regs in structs will allow this behavior

// Unions allocate space for largest member and all members share memory
// when we set AF, F and A will give us corresponding bytes
    union {
        u16 AF;
        struct {
            u8 F; // Little Endian, least significant byte stores in lowest memory address
            u8 A; // high byte
        };
    } regAF;

    union {
        u16 BC;
        struct {
            u8 C;
            u8 B;
        };
    } regBC;

    union {
        u16 DE;
        struct {
            u8 E;
            u8 D;
        };
    } regDE;

    union {
        u16 HL;
        struct {
            u8 L;
            u8 H;
        };
    } regHL;

    u16 SP; // stack pointer
    u16 PC; // program counter

public:
    CPU();
    u8 fetchInstruction(Memory& memory);
    void decodeInstruction();
    void executeInstruction(Memory& memory);
    void reset();
    u8& getA();
    u8& getF();
    u16& getAF();

};
#endif
