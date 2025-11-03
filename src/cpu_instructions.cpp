#include "../include/cpu.hpp"
#include "../include/memory.hpp"



    void CPU::NOP() {
        // No operation
    }

    // LD BC, n16: Load 16-bit immediate into BC
    // 3 bytes (PC++ then +2), 12t cycles
    void CPU::LD_BC_n16(Memory& memory) {
        u16 val = memory.readWord(m_PC);
        m_B = val >> 8;
        m_C = val & 0xFF;
        m_PC += 2;
    }

    void CPU::LD_mBC_A(Memory& memory);
    void CPU::INC_BC();
    void CPU::INC_B();
    void CPU::DEC_B();
    void CPU::LD_B_n8(Memory& memory);
    void CPU::RLCA();
    void CPU::LD_mn16_SP(Memory& memory);
    void CPU::ADD_HL_BC();
    void CPU::LD_A_mBC(Memory& memory);
    void CPU::DEC_BC();
    void CPU::INC_C();
    void CPU::DEC_C();
    void CPU::LD_C_n8(Memory& memory);
    void CPU::RRCA();
    void CPU::STOP();