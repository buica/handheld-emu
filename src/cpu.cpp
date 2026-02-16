#include "../include/cpu.hpp"
#include "../include/memory.hpp"
#include "cpu_instructions.cpp"
#include <iostream>


CPU::CPU() {
    initRegisters();
}

// For debugging: print out CPU state to log
void CPU::printCPU() {
    std::clog << "CPU State:" << std::endl;
    std::clog << "A: " << std::hex << static_cast<int>(getA()) << std::endl;
    std::clog << "B: " << std::hex << static_cast<int>(getB()) << std::endl;
    std::clog << "C: " << std::hex << static_cast<int>(getC()) << std::endl;
    std::clog << "D: " << std::hex << static_cast<int>(getD()) << std::endl;
    std::clog << "E: " << std::hex << static_cast<int>(getE()) << std::endl;
    std::clog << "F: " << std::hex << static_cast<int>(getF()) << std::endl;
    std::clog << "H: " << std::hex << static_cast<int>(getH()) << std::endl;
    std::clog << "L: " << std::hex << static_cast<int>(getL()) << std::endl;
    std::clog << "AF: " << std::hex << getAF() << std::endl;
    std::clog << "BC: " << std::hex << getBC() << std::endl;
    std::clog << "DE: " << std::hex << getDE() << std::endl;
    std::clog << "HL: " << std::hex << getHL() << std::endl;
    std::clog << "SP: " << std::hex << getSP() << std::endl;
    std::clog << "PC: " << std::hex << getPC() << std::endl;
}

u8 CPU::getA() const { return m_A; }
u8 CPU::getB() const { return m_B; }
u8 CPU::getC() const { return m_C; }
u8 CPU::getD() const { return m_D; }
u8 CPU::getE() const { return m_E; }
u8 CPU::getF() const { return m_F; }
u8 CPU::getH() const { return m_H; }
u8 CPU::getL() const { return m_L; }

// these 16-bit registers form from combining pairs of 8-bit registers
u16 CPU::getAF() const { return (static_cast<u16>(m_A) << 8) | m_F; } //lower 8 bits are flags
u16 CPU::getBC() const { return (static_cast<u16>(m_B) << 8) | m_C; }
u16 CPU::getDE() const { return (static_cast<u16>(m_D) << 8) | m_E; }
u16 CPU::getHL() const { return (static_cast<u16>(m_H) << 8) | m_L; }

u16 CPU::getSP() const { return m_SP; }
u16 CPU::getPC() const { return m_PC; }

void CPU::setA(u8 val) {
    m_A = val;
}
void CPU::setB(u8 val) {
    m_B = val;
}
void CPU::setC(u8 val) {
    m_C = val;
}
void CPU::setD(u8 val) {
    m_D = val;
}
void CPU::setE(u8 val) {
    m_E = val;
}

void CPU::setF(u8 val) {
    m_F = val;
}
void CPU::setH(u8 val) {
    m_H = val;
}
void CPU::setL(u8 val) {
    m_L = val;
}

void CPU::setAF(u16 val) {
    m_A = static_cast<u8>(val >> 8);
    m_F = static_cast<u8>(val & 0xFF);
}

void CPU::setBC(u16 val) {
    m_B = static_cast<u8>(val >> 8);
    m_C = static_cast<u8>(val & 0xFF);
}

void CPU::setDE(u16 val) {
    m_D = static_cast<u8>(val >> 8);
    m_E = static_cast<u8>(val & 0xFF);
}

void CPU::setHL(u16 val) {
    m_H = static_cast<u8>(val >> 8);
    m_L = static_cast<u8>(val & 0xFF);
}

void CPU::setSP(u16 val) {
    m_SP = val;
}

void CPU::setPC(u16 val) {
    m_PC = val;
}

/**
 * @brief Sets or clears the Zero Flag (Z) in the F register.
 * @param set true sets bit 7 of the F register; false clears it.
 * @details Set if and only if result of an operation is zero.
 * Used after arithmetic/logic operations, and conditional jumps.
 */
void CPU::setZeroFlag(bool set) {
    if (set) {
        m_F |= 0x80; // set bit 7
    } else {
        m_F &= ~0x80; // clear bit 7 and leave all others untouched
    }
}

/**
* @brief Sets or clears the Subtraction Flag (N) in the F register.
* @param set true sets bit 6 of the F register; false clears it.
* @details Indicates whether previous instruction has been a subtraction
*/
void CPU::setSubtractionFlag(bool set) {
    if (set) {
        m_F |= 0x40; // set bit 6
    } else {
        m_F &= ~0x40; // clear bit 6 and leave all others untouched
    }
}

/**
* @brief Sets or clears the Half Carry Flag (H) in the F register.
* @param set true sets bit 5 of the F register; false clears it.
* @details */
void CPU::setHalfCarryFlag(bool set) {
    if (set) {
        m_F |= 0x20; // set bit 5
    } else {
        m_F &= ~0x20; // clear bit 5 and leave all others untouched
    }
}

/**
* @brief Sets or clears the Carry Flag (C) in the F register.
* @param set true sets bit 4 of the F register; false clears it.
* @details Is set in these cases:
            - when result of 8-bit addtion is higher than $FF
            - when result of 16-bit addition is higher than $FFFF
            - when result of subtraction or comparison is lower
              than zero
            - when a rotate/shift operation shifts out a 1 bit
*/
void CPU::setCarryFlag(bool set) {
    if (set) {
        m_F |= 0x10; // set bit 4
    } else {
        m_F &= ~0x10; // clear bit 4 and leave all others untouched
    }
}

bool CPU::getZeroFlag() const {
    u8 zero_bit = (getF() >> 7) & 0x01; // flag bits reside in F register
    return zero_bit != 0;
}

bool CPU::getSubtractionFlag() const {
    u8 subtraction_bit = (getF() >> 6) & 0x01;
    return subtraction_bit != 0;
}

bool CPU::getHalfCarryFlag() const {
    u8 halfcarry_bit = (getF() >> 5) & 0x01;
    return halfcarry_bit != 0;
}

bool CPU::getCarryFlag() const {
    u8 carry_bit = (getF() >> 4) & 0x01;
    return carry_bit != 0;
}

/*
 * Initialize registers to boot vals WIP
 */
void CPU::initRegisters() {
    m_A = 0x00;
    m_B = 0x00;
    m_C = 0x00;
    m_D = 0x00;
    m_E = 0x00;
    m_H = 0x00;
    m_L = 0x00;
    m_SP = 0x0000;
    m_PC = 0x0100; // our emu doesnt care about boot ROM sequence, start game ROM
}

/*
*
*/
u8 CPU::fetchInstruction(Memory& memory) {
    // get the opcode and increment PC
    u8 opcode = memory.readByte(m_PC++);
    return opcode;
}

// TODO: refactor once the switch cases start getting too long (maybe lookup table)
void CPU::executeInstruction(Memory& memory) {
    u8 opcode = fetchInstruction(memory);

    // decode and execute
    // Build up most essential instructions first
    // Flags: Z (zero), N (negative:add/sub), H (half carry), C (carry)


    // For full instruction info incl. flag behavior,
    // use: https://rgbds.gbdev.io/docs/v0.9.4/gbz80.7
    switch(opcode) {
        case 0x00:
            NOP();
            break;

        case 0x01:
            LD_BC_n16(memory);
            break;

        case 0x02:
            LD_mBC_A(memory);
            break;

        case 0x03:
            INC_BC();
            break;

        case 0x04:
            INC_B();
            break;

        case 0x05:
            DEC_B();
            break;

        case 0x06:
            LD_B_n8(memory);
            break;

        case 0x07:
            RLCA();
            break;

        case 0x08:
            LD_mn16_SP(memory);
            break;

        case 0x09:
            ADD_HL_BC();
            break;

        case 0x0A:
            LD_A_mBC(memory);
            break;

        case 0x0B:
            DEC_BC();
            break;

        case 0x0C:
            INC_C();
            break;

        case 0x0D:
            DEC_C();
            break;

        case 0x0E:
            LD_C_n8(memory);
            break;

        case 0x0F:
            RRCA();
            break;

        case 0x10:
            STOP();
            break;

        case 0x11:
            LD_DE_n16(memory);
            break;

        case 0x12:
            LD_mDE_A(memory);
            break;

        case 0x13:
            INC_DE();
            break;

        case 0x14:
            INC_D();
            break;

        case 0x15:
            DEC_D();
            break;

        case 0x16:
            LD_D_n8(memory);
            break;

        case 0x17:
            RLA();
            break;

        case 0x18:
            JR_e8(memory);
            break;

        case 0x19:
            ADD_HL_DE();
            break;

        case 0x1A:
            LD_A_mDE(memory);
            break;

        case 0x1B:
            DEC_DE();
            break;

        case 0x1C:
            INC_E();
            break;

        case 0x1D:
            DEC_E();
            break;

        case 0x1E:
            LD_E_n8(memory);
            break;

        case 0x1F:
            RRA();
            break;

        case 0x20:
            JR_NZ_e8(memory);
            break;

        case 0x21:
            LD_HL_n16(memory);
            break;

        case 0x22:
            LD_mHLinc_A(memory);
            break;

        case 0x23:
            INC_HL();
            break;

        case 0x24:
            INC_H();
            break;

        case 0x25:
            DEC_H();
            break;

        case 0x26:
            LD_H_n8(memory);
            break;

        case 0x27:
            DAA();
            break;

        case 0x28:
            JR_Z_e8(memory);
            break;

        case 0x29:
            ADD_HL_HL();
            break;

        case 0x2A:
            LD_A_mHLinc(memory);
            break;

        case 0x2B:
            DEC_HL();
            break;

        case 0x2C:
            INC_L();
            break;

        case 0x2D:
            DEC_L();
            break;

        case 0x2E:
            LD_L_n8(memory);
            break;

        case 0x2F:
            CPL();
            break;

        case 0x30:
            JR_NC_e8(memory);
            break;

        case 0x31:
            LD_SP_n16(memory);
            break;

        case 0x32:
            LD_mHLdec_A(memory);
            break;

        case 0x33:
            INC_SP();
            break;

        case 0x34:
            INC_mHL(memory);
            break;

        case 0x35:
            DEC_mHL(memory);
            break;

        case 0x36:
            LD_mHL_n8(memory);
            break;

        case 0x37:
            SCF();
            break;

        case 0x38:
            JR_C_e8(memory);
            break;

        case 0x39:
            ADD_HL_SP();
            break;

        case 0x3A:
            LD_A_mHLdec(memory);
            break;

        case 0x3B:
            DEC_SP();
            break;

        case 0x3C:
            INC_A();
            break;

        case 0x3D:
            DEC_A();
            break;

        case 0x3E:
            LD_A_n8(memory);
            break;

        case 0x3F:
            CCF();
            break;

        case 0x40:
            LD_B_B();
            break;

        case 0x41:
            LD_B_C();
            break;

        case 0x42:
            LD_B_D();
            break;

        case 0x43:
            LD_B_E();
            break;

        case 0x44:
            LD_B_H();
            break;

        case 0x45:
            LD_B_L();
            break;

        case 0x46:
            LD_B_mHL(memory);
            break;

        case 0x47:
            LD_B_A();
            break;

        case 0x48:
            LD_C_B();
            break;

        case 0x49:
            LD_C_C();
            break;

        case 0x4A:
            LD_C_D();
            break;

        case 0x4B:
            LD_C_E();
            break;

        case 0x4C:
            LD_C_H();
            break;

        case 0x4D:
            LD_C_L();
            break;

        case 0x4E:
            LD_C_mHL(memory);
            break;

        case 0x4F:
            LD_C_A();
            break;

        case 0x50:
            LD_D_B();
            break;

        case 0x51:
            LD_D_C();
            break;

        case 0x52:
            LD_D_D();
            break;

        case 0x53:
            LD_D_E();
            break;

        case 0x54:
            LD_D_H();
            break;

        case 0x55:
            LD_D_L();
            break;

        case 0x56:
            LD_D_mHL(memory);
            break;

        case 0x57:
            LD_D_A();
            break;

        case 0x58:
            LD_E_B();
            break;

        case 0x59:
            LD_E_C();
            break;

        case 0x5A:
            LD_E_D();
            break;

        case 0x5B:
            LD_E_E();
            break;

        case 0x5C:
            LD_E_H();
            break;

        case 0x5D:
            LD_E_L();
            break;

        case 0x5E:
            LD_E_mHL(memory);
            break;

        case 0x5F:
            LD_E_A();
            break;

        case 0x60:
            LD_H_B();
            break;

        case 0x61:
            LD_H_C();
            break;

        case 0x62:
            LD_H_D();
            break;

        case 0x63:
            LD_H_E();
            break;

        case 0x64:
            LD_H_H();
            break;

        case 0x65:
            LD_H_L();
            break;

        case 0x66:
            LD_H_mHL(memory);
            break;

        case 0x67:
            LD_H_A();
            break;

        case 0x68:
            LD_L_B();
            break;

        case 0x69:
            LD_L_C();
            break;

        case 0x6A:
            LD_L_D();
            break;

        case 0x6B:
            LD_L_E();
            break;

        case 0x6C:
            LD_L_H();
            break;

        case 0x6D:
            LD_L_L();
            break;

        case 0x6E:
            LD_L_mHL(memory);
            break;

        case 0x6F:
            LD_L_A();
            break;

        case 0x70:
            LD_mHL_B(memory);
            break;

        case 0x71:
            LD_mHL_C(memory);
            break;

        case 0x72:
            LD_mHL_D(memory);
            break;

        case 0x73:
            LD_mHL_E(memory);
            break;

        case 0x74:
            LD_mHL_H(memory);
            break;

        case 0x75:
            LD_mHL_L(memory);
            break;

        case 0x76:
            HALT();
            break;

        case 0x77:
            LD_mHL_A(memory);
            break;

        case 0x78:
            LD_A_B();
            break;

        case 0x79:
            LD_A_C();
            break;

        case 0x7A:
            LD_A_D();
            break;

        case 0x7B:
            LD_A_E();
            break;

        case 0x7C:
            LD_A_H();
            break;

        case 0x7D:
            LD_A_L();
            break;

        case 0x7E:
            LD_A_mHL(memory);
            break;

        case 0x7F:
            LD_A_A();
            break;




        // HALT
        case 0x76:
            // enter low power mode until an interrupt occurs
            // for now, just print and exit
            std::cout << "HALT encountered. Exiting." << std::endl;
            exit(0);
            break;


        case 0xC9:
            RET();
            break;

        default:
            std::cerr << std::format("Exec Error! Opcode {:#02x} PC: {:#04x}\n", opcode, m_PC - 1);
            printCPU();
            exit(1);
            break;

    }

}
