#ifndef CPU_HPP
#define CPU_HPP

#include "common.hpp"
#include "memory.hpp"
#include <atomic>

//to do:
// - read more about z80/8080 cpu architecture
// - implement constants
// - implement isa gradually, high priority opcodes first
// - use blarg's test roms to test
// - cpu.step()



class CPU {
public:
    CPU();
    void printCPU();
    //void reset(); can't we just use initRegisters() in place of this?
    u8& getA();
    u8& getB();
    u8& getC();
    u8& getD();
    u8& getE();
    u8& getF();
    u8& getH();
    u8& getL();
    u16& getAF();
    u16& getBC();
    u16& getDE();
    u16& getHL();
    u16& getSP();
    u16& getPC();


private:
    void initRegisters();
    u8 fetchInstruction(Memory& memory);
    // void decodeInstruction();
    void executeInstruction(Memory& memory);

    // We need to be able to access same registers as 16bit regsters and as 2 separate 8bit registers.
    // We'll use unions along with grouping the 8bit regs within structs to implement this.
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

    u16 SP;
    u16 PC;
    u8 cycles;
};

#endif
