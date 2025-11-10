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

void CPU::setA(u8 value) {
    m_A = value;
}
void CPU::setB(u8 value) {
    m_B = value;
}
void CPU::setC(u8 value) {
    m_C = value;
}
void CPU::setD(u8 value) {
    m_D = value;
}
void CPU::setE(u8 value) {
    m_E = value;
}

void CPU::setF(u8 value) {
    m_F = value;
}
void CPU::setH(u8 value) {
    m_H = value;
}
void CPU::setL(u8 value) {
    m_L = value;
}

// TODO: implement the other flag bits setters

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


/*
 * Initialize registers to boot values WIP
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

        case 0x06: {
            LD_B_n8(memory);
            break;
        }

        case 0x07: {
            RLCA();
            break;
        }

        case 0x08: {
            LD_mn16_SP(memory);
            break;
        }

        case 0x09: {
            ADD_HL_BC();
            break;

        }
        case 0x0A:
            LD_A_mBC(memory);
            break;

        case 0x0B: {
            DEC_BC();
            break;
        }
        case 0x0C:
            INC_C();
            break;

        case 0x0D:
            DEC_C();
            break;

        case 0x0E:
            LD_C_n8(memory);
            break;

        case 0x0F: {
            RRCA();
            break;
        }

        case 0x10: {
            STOP();
            break;
        }

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
            // INC_D();
            break;

        case 0x15:
            // DEC_D();
            break;

        case 0x16:
            // LD_D_n8(memory);
            break;
        case 0x17:
            // RLA();
            break;

        case 0x18:
            // JR_n8(memory);
            break;

        case 0x19:

            // ADD_HL_DE();
            break;

        case 0x1A:
            // LD_A_mDE(memory);
            break;


        // HALT
        // 1 byte, 4t cycles
        case 0x76: {
            // enter low power mode until an interrupt occurs
            // for now, just print and exit
            std::cout << "HALT encountered. Exiting." << std::endl;
            exit(0);
            break;
        }

        default:
            std::cerr << std::format("Exec Error! Opcode {:#02x} PC: {:#04x}\n", opcode, m_PC - 1);
            printCPU();
            exit(1);
            break;

    }

}
