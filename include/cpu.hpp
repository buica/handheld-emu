#pragma once

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

    u8 getA() const;
    u8 getB() const;
    u8 getC() const;
    u8 getD() const;
    u8 getE() const;
    u8 getF() const;
    u8 getH() const;
    u8 getL() const;
    u16 getAF() const;
    u16 getBC() const;
    u16 getDE() const;
    u16 getHL() const;
    u16 getSP() const;
    u16 getPC() const;

    void setA(u8 value);
    void setB(u8 value);
    void setC(u8 value);
    void setD(u8 value);
    void setE(u8 value);
    void setF(u8 value);
    void setH(u8 value);
    void setL(u8 value);

    void setZeroFlag(bool set);
    void setSubtractionFlag(bool set);
    void setHalfCarryFlag(bool set);
    void setCarryFlag(bool set);

private:
    void initRegisters();
    u8 fetchInstruction(Memory& memory);
    // void decodeInstruction();
    void executeInstruction(Memory& memory);

    u8 m_A;
    u8 m_B;
    u8 m_C;
    u8 m_D;
    u8 m_E;
    u8 m_F;
    u8 m_H;
    u8 m_L;

    u16 m_SP;
    u16 m_PC;
    u8 m_cycles;
};
