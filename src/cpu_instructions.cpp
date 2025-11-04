#include "../include/cpu.hpp"
#include "../include/memory.hpp"


    // NOP
    // 1 byte (taken care of by PC++), 4t cycles (4 t-cycles = 1 machine cycle)
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

    // LD (BC), A: Store A into address pointed by BC
    // 1 byte, 8t cycles
    void CPU::LD_mBC_A(Memory& memory) {
        u16 address = getBC();
        memory.writeByte(address, m_A);
    }

    // INC BC: Increment BC
    // 1 byte, 8t cycles
    void CPU::INC_BC() {
        u16 bc = getBC();
        bc++;
        // assign relevant bytes back to B and C
        m_B = bc >> 8; // keep upper 8 bits
        m_C = bc & 0xFF; // mask upper 8 bits to keep lower 8 bits
    }

    // INC B
    // 1 byte , 4t cycles
    // Z, 0, H, -
    void CPU::INC_B() {
        u8 b = getB();
        u8 new_b = b + 1;
        setB(new_b);

        setZeroFlag(new_b == 0);
        setSubtractionFlag(false);

        bool hasHalfCarry = (b & 0x0F) == 0x0F; // check if lower nibble overflows
        setHalfCarryFlag(hasHalfCarry);
    }

    // DEC B
    // 1 byte, 4t cycles
    // Z, 1, H, -
    void CPU::DEC_B() {
        u8 b = getB();
        u8 new_b = b - 1;
        setB(new_b);

        setZeroFlag(new_b == 0);
        setSubtractionFlag(true);

        bool hasHalfCarry = (b & 0x0F) == 0x00; // check if lower nibble underflows
        setHalfCarryFlag(hasHalfCarry);
    }

    // LD B, n8: Load 8-bit immediate into B
    // 2 bytes, 8t cycles
    void CPU::LD_B_n8(Memory& memory) {
        u8 val = memory.readByte(m_PC);
        setB(val);
        m_PC++;
    }

    // RLCA: Rotate reg A('s bits) left by 1.
    // bit 7 moves to bit 0 and Carry flag.
    // 1 byte, 4t cycles
    void CPU::RLCA() {
        u8 a = getA();
        u8 bit7 = (a & 0x80) >> 7;
        u8 rotatedA = (a << 1) | bit7; // shift bits & put bit7 into bit0
        setA(rotatedA);
        // setCarryFlag()
    }

    // LD (n16), SP: store stack ptr into memory addr given by 16-bit immediate value.
    // 3 bytes, 20t cycles (w/o branch)
    void CPU::LD_mn16_SP(Memory& memory) {
        u16 sp = getSP();
        u16 immediate = memory.readWord(m_PC);
        memory.writeByte(immediate, sp & 0xFF);     // Little endian: low byte first
        memory.writeByte(immediate + 1, sp >> 8);
        m_PC += 2;
    }

    // ADD HL, BC
    // 1 byte, 8t cycles
    void CPU::ADD_HL_BC() {
        // must add low bytes L + C then use carry/half carry
        // for high byte add H + B
        u16 hl = getHL();
        u16 bc = getBC();
        u32 result = static_cast<u32>(hl) + static_cast<u32>(bc);
        m_H = (result >> 8) & 0xFF;
        m_L = result & 0xFF;

        bool hasCarry = result > 0xFFFF;
        bool hasHalfCarry = (hl & 0x0FFF) + (bc & 0x0FFF) > 0x0FFF;

        setZeroFlag(false);
        setSubtractionFlag(false);
        setCarryFlag(hasCarry);
        setHalfCarryFlag(hasHalfCarry);
    }

    // LD A, (BC): load the bye pointed to by BC into register A
    // 1 byte, 8t cycles
    void CPU::LD_A_mBC(Memory& memory) {

    }

    void CPU::DEC_BC() {

    }

    void CPU::INC_C() {

    }

    void CPU::DEC_C() {

    }

    void CPU::LD_C_n8(Memory& memory) {

    }

    void CPU::RRCA() {

    }

    // STOP
    // 2 bytes, 4t cycles
    void CPU::STOP() {
        m_PC++; // 2-byte instruction: opcode 0x10 + second 0x00 byte
        // read more about STOP instruction:
        // https://gbdev.io/pandocs/Reducing_Power_Consumption.html#using-the-stop-instruction
    }