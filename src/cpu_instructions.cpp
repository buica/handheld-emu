#include "../include/cpu.hpp"
#include "../include/memory.hpp"



// 0x00 No operation
// 1 byte (taken care of by PC++), 4t cycles (4 t-cycles = 1 machine cycle)
void CPU::NOP() {}

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

// Increment BC
// 1 byte, 8t cycles
void CPU::INC_BC() {
    u16 bc = getBC();
    bc++;
    // assign relevant bytes back to B and C
    m_B = bc >> 8; // keep upper 8 bits
    m_C = bc & 0xFF; // mask upper 8 bits to keep lower 8 bits
}

// increment B
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

// 0x05 decrement B
// 1 byte, 4t cycles
// Z, 1, H, -s
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

// RLCA: Rotate A's bits left by 1.
// bit 7 moves to bit 0 and Carry flag.
// 1 byte, 4t cycles
void CPU::RLCA() {
    u8 a = getA();
    u8 bit7 = (a & 0x80) >> 7;

    u8 rotatedA = (a << 1) | bit7; // shift bits & put bit7 into bit0
    setA(rotatedA);

    setCarryFlag(true);
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

// 0x0A
// LD A, (BC): load into register A the byte at address contained in register BC
// 1 byte, 8t cycles
void CPU::LD_A_mBC(Memory& memory) {
    u16 address = getBC();
    u8 val = memory.readByte(address);
    setA(val);
}

// Decrement BC
// 1 byte, 8t cycles
void CPU::DEC_BC() {
    u16 bc = getBC();
    bc--;

    m_B = bc >> 8;
    m_C = bc & 0xFF;
}

// increment C
// 1 byte, 4t cycles
void CPU::INC_C() {
    u8 c = getC();
    u8 new_c = c + 1;
    setC(new_c);

    setZeroFlag(new_c == 0);
    setSubtractionFlag(false);
    bool hasHalfCarry = (c & 0x0F) == 0x0F; // check if lower nibble overflows
    setHalfCarryFlag(hasHalfCarry);
}

// decrement C
// 1 byte, 4t cycles
void CPU::DEC_C() {
    u8 c = getC();
    u8 new_c = c - 1;
    setC(new_c);

    setZeroFlag(new_c == 0);
    setSubtractionFlag(true);
    bool hasHalfCarry = (c & 0x0F) == 0x00; // check if lower nibble underflows
    setHalfCarryFlag(hasHalfCarry);
}

// LD C, n8: Load 8-bit immediate into C
// 2 bytes, 8t cycles
void CPU::LD_C_n8(Memory& memory) {
    u8 val = memory.readByte(m_PC);
    setC(val);
    m_PC++;
}

// rotate A's bits right by 1
// bit 0 goes to bit 7 and Carry flag.
void CPU::RRCA() {
    u8 a = getA();
    u8 bit0 = a & 0x01;
    u8 rotatedA = (a >> 1) | bit0;
    setA(rotatedA);

    setCarryFlag(true);
}

// 0x10 STOP
// 2 bytes, 4t cycles
void CPU::STOP() {
    m_PC++; // 2-byte instruction: opcode 0x10 + second 0x00 byte
    // read more about STOP instruction:
    // https://gbdev.io/pandocs/Reducing_Power_Consumption.html#using-the-stop-instruction
}

// LD DE, n16: Load 16-bit immediate into DE
// 3 bytes, 12t cycles
void CPU::LD_DE_n16(Memory& memory) {
    u16 val = memory.readWord(m_PC);
    m_D = val >> 8;
    m_E = val & 0xFF;
    m_PC += 2;
}

// LD (DE), A: Store A into address pointed by DE
// 1 byte, 8t cycles
void CPU::LD_mDE_A(Memory& memory) {
    u16 address = getDE();
    memory.writeByte(address, m_A);
}

// increment DE
// 1 byte, 8t cycles
void CPU::INC_DE() {
    u16 de = getDE();
    de++;

    m_D = de >> 8;
    m_E = de & 0xFF;
}

// increment D
// 1 byte , 4t cycles
void CPU::INC_D() {
    u8 d = getD();
    u8 new_d = d + 1;
    setD(new_d);

    setZeroFlag(new_d == 0);
    setSubtractionFlag(false);
    bool hasHalfCarry = (d & 0x0F) == 0x0F;
    setHalfCarryFlag(hasHalfCarry);
}

// 0x15
// Decrement D
// 1 byte, 4t cycles
void CPU::DEC_D() {
    u8 d = getD();
    u8 new_d = d - 1;
    setD(new_d);

    setZeroFlag(new_d == 0);
    setSubtractionFlag(true);
    bool hasHalfCarry = (d & 0x0F) == 0x00;
    setHalfCarryFlag(hasHalfCarry);
}

// LD D, n8: Load 8-bit immediate into D
// 2 bytes, 8t cycles
void CPU::LD_D_n8(Memory& memory) {
    u8 val = memory.readByte(m_PC);
    setD(val);
    m_PC++;
}

// rotate reg A left through carry flag
// 1 byte, 4t cycles
void CPU::RLA() {
    u8 a = getA();
    u8 carry_bit = (getF() >> 4) & 0x01; // get current carry flag (F register lower nibble contains flags)
    u8 bit7 = (a & 0x80) >> 7;
    u8 rotated_a = (a << 1) | carry_bit; // carry rotates into bit0
    setA(rotated_a);

    setCarryFlag(bit7);
}

// Relative jump to signed immediate e8 (-128 to +127)
// e8 is 8-bit offset from the address immediately following JR
// 2 bytes, 12t cycles
void CPU::JR_e8(Memory& memory) {
    i8 offset = static_cast<i8>(memory.readByte(m_PC));
    m_PC++;
    m_PC += offset; // target addresss
}

// ADD val in DE to HL
// 1 byte, 8t cycles
void CPU::ADD_HL_DE() {
    u16 hl = getHL();
    u16 de = getDE();

    u32 result = static_cast<u32>(hl) + static_cast<u32>(de);
    m_H = (result >> 8) & 0xFF;
    m_L = result & 0xFF;

    bool hasCarry = result > 0xFFFF;
    bool hasHalfCarry = (hl & 0x0FFF) + (de & 0x0FFF) > 0x0FFF;
    setZeroFlag(false);
    setSubtractionFlag(false);
    setCarryFlag(hasCarry);
    setHalfCarryFlag(hasHalfCarry);
}

// 0x1A
// LD A, (DE): load the byte that address of register DE contains into register A
// 1 byte, 8t cycles
void CPU::LD_A_mDE(Memory& memory) {
    u16 address = getDE();
    u8 val = memory.readByte(address);
    setA(val);
}

// Decrement DE
// 1 byte, 8t cycles
void CPU::DEC_DE() {
    u16 de = getDE();
    de--;
    m_D = de >> 8;
    m_E = de & 0xFF;
}

// increment E
// 1 byte , 4t cycles
void CPU::INC_E() {
    u8 e = getE();
    u8 new_e = e + 1;
    setE(new_e);

    setZeroFlag(new_e == 0);
    setSubtractionFlag(false);
    bool hasHalfCarry = (e & 0x0F) == 0x0F;
    setHalfCarryFlag(hasHalfCarry);
}

// decrement E
// 1 byte, 4t cycles
void CPU::DEC_E() {
    u8 e = getE();
    u8 new_e = e - 1;
    setE(new_e);

    setZeroFlag(new_e == 0);
    setSubtractionFlag(true);
    bool hasHalfCarry = (e & 0x0F) == 0x00;
    setHalfCarryFlag(hasHalfCarry);
}

// LD E, n8: Load 8-bit immediate into E
// 2 bytes, 8t cycles
void CPU::LD_E_n8(Memory& memory) {
    u8 val = memory.readByte(m_PC);
    setE(val);
    m_PC++;
}

// rotate reg A right through carry flag
// 1 byte, 4t cycles
void CPU::RRA() {
    u8 a = getA();
    u8 carry = (getF() >> 4) & 0x01; // get current carry flag (F register lower nibble contains flags)
    u8 bit0 = a & 0x01;
    u8 rotatedA = (a >> 1) | (carry << 7); // carry rotates into bit7
    setA(rotatedA);

    setCarryFlag(bit0);
}

// relative jump to signed 8-bit immediate if Z flag is not set
// 2 bytes, 12t cycles if jump, 8t if no jump
// range of relative jump for i8: -128 to 127
void CPU::JR_NZ_e8(Memory& memory) {
    i8 offset = static_cast<i8>(memory.readByte(m_PC));
    m_PC++;

    if (!getZeroFlag()) {
        m_PC += offset;
    }
}

// Load 16-bit immediate into HL
// 3 bytes, 12t cycles
void CPU::LD_HL_n16(Memory& memory) {
    u16 val = memory.readWord(m_PC);
    m_H = val >> 8;
    m_L = val & 0xFF;
    m_PC++;
}

// load val in reg A into address pointed to by HL then post-increment HL
// 1 byte, 8t cycles
void CPU::LD_mHLp_A(Memory& memory) {
    u16 address = getHL();
    memory.writeByte(address, m_A);
    INC_HL();
}

// increment HL
// 1 byte, 8t cycles
void CPU::INC_HL() {
    u16 hl = getHL();
    hl++;
    m_H = hl >> 8;
    m_L = hl & 0xFF;
}

// increment H
// 1 byte , 4t cycles
void CPU::INC_H() {
    u8 h = getH();
    u8 new_h = h + 1;

    setH(new_h);
    setZeroFlag(new_h == 0);
    setSubtractionFlag(false);
    bool hasHalfCarry = (h & 0x0F) == 0x0F;
    setHalfCarryFlag(hasHalfCarry);
}

// 0x25
// decrement H
// 1 byte, 4t cycles
void CPU::DEC_H() {
    u8 h = getH();
    u8 new_h = h - 1;

    setH(new_h);
    setZeroFlag(new_h == 0);
    setSubtractionFlag(true);
    bool hasHalfCarry = (h & 0x0F) == 0x0F;
    setHalfCarryFlag(hasHalfCarry);
}

// Load 8-bit immediate into H
// 2 bytes, 8t cycles
void CPU::LD_H_n8(Memory& memory) {
    u8 val = memory.readByte(m_PC);
    setH(val);
    m_PC++;
}

// Decimal Adjust Accumulator
// 1 byte, 4t cycles
// Behavior depends on the state of subtraction N flag:
// if N flag is set
//   - init adjustment to 0
//   - if H flag is set, add 0x06 to adjustment
//   - if C flag is set, add 0x60 to adjustment
//   - subtract adjustment from A
// if N flag is not set
//   - init adjustment to 0
//   - if H flag is set or A & 0x0F > 9, add 0x06 to adjustment
//   - if C flag is set or A > 0x99, add 0x60 to adjustment
//   - add adjustment to A
// - set Z flag if A is zero
void CPU::DAA() {
    u8 a = getA();
    u8 adjustment = 0;
}

// relative jump to signed 8-bit immediate if Z flag is set
// 2 bytes, 12t cycles if jump, 8t if no jump
void CPU::JR_Z_e8(Memory& memory) {
    i8 offset = static_cast<i8>(memory.readByte(m_PC));
    m_PC++;

    if (getZeroFlag()) {
        m_PC += offset;
    }
}

