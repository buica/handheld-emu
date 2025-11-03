#include "../include/cpu.hpp"
#include "../include/memory.hpp"
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
        // NOP
        // 1 byte (taken care of by PC++), 4t cycles (4 t-cycles = 1 machine cycle)
        case 0x00:
            NOP();
            break;

        case 0x01:
            LD_BC_n16(memory);
            break;
        // LD (BC), A: Store A into address pointed by BC
        // 1 byte, 8t cycles
        case 0x02: {
            u16 address = getBC();
            memory.writeByte(address, m_A);
            break;
        }
        // INC BC: Increment BC
        // 1 byte, 8t cycles
        case 0x03: {
            u16 bc = getBC();
            bc++;
            // assign relevant bytes back to B and C
            m_B = bc >> 8; // keep upper 8 bits
            m_C = bc & 0xFF; // mask upper 8 bits to keep lower 8 bits
            break;
        }
        // INC B
        // 1 byte , 4t cycles
        // Z, 0, H, -
        case 0x04: {
            u8 b = getB() + 1;
            setB(b);
            // set flags
            setZeroFlag(b == 0);
            // to-do: other 3 flags
            break;
        }
        // DEC B
        // 1 byte, 4t cycles
        // Z, 1, H, -
        case 0x05: {
            u8 b = getB() - 1;
            setB(b);
            setZeroFlag(b == 0);
            // to-do: other 3 flags
            break;
        }
        // LD B, n8: Load 8-bit immediate into B
        // 2 bytes, 8t cycles
        case 0x06: {
            u8 val = memory.readByte(m_PC);
            setB(val);
            m_PC++;
            break;
        }
        // RLCA: Rotate reg A('s bits) left by 1.
        // bit 7 moves to bit 0 and Carry flag.
        // 1 byte, 4t cycles
        // 0, 0, 0, C
        case 0x07: {
            u8 a = getA();
            u8 bit7 = (a & 0x80) >> 7;
            u8 rotatedA = (a << 1) | bit7; // shift bits & put bit7 into bit0
            setA(rotatedA);
            // setCarryFlag()
        }
        // LD (n16), SP: store stack ptr into memory addr given by 16-bit immediate value.
        // 3 bytes, 20t cycles (w/o branch)
        case 0x08: {
            u16 sp = getSP();
            u16 immediate = memory.readWord(m_PC);
            memory.writeByte(immediate, sp & 0xFF);     // Little endian: low byte first
            memory.writeByte(immediate + 1, sp >> 8);
            m_PC += 2;
            break;
        }
        // ADD HL, BC
        // 1 byte, 8t cycles
        case 0x09: {
            // must add low bytes L + C then use carry/half carry
            // for high byte add H + B
            u16 hl = getHL();
            u16 bc = getBC();
            u32 result = static_cast<u32>(hl) + static_cast<u32>(bc);

            m_H = (result >> 8) & 0xFF;
            m_L = result & 0xFF;

            bool hasCarry = result > 0xFFFF;
            bool hasHalfCarry = (hl & 0x0FFF) + (bc & 0x0FFF) > 0x0FFF;
            // set flags
            setZeroFlag(false);
            setSubtractionFlag(false);
            setCarryFlag(hasCarry);
            setHalfCarryFlag(hasHalfCarry);
            break;

        }
        case 0x0A:
            LD_A_mBC(m_PC);
            break;


        // STOP
        // 2 bytes, 4t cycles
        case 0x10: {
            m_PC++;
            break;
            // read more about STOP instruction:
            // https://gbdev.io/pandocs/Reducing_Power_Consumption.html#using-the-stop-instruction
        }


        // HALT
        // 1 byte, 4t cycles
        case 0x76: {
            // enter low power mode until an interrupt occurs
            // for now, just print and exit
            std::cout << "HALT encountered. Exiting." << std::endl;
            exit(0);
            break;
        }

        default: {
            std::cerr << "Opcode Not Yet Implemented: 0x" << std::hex << (int)opcode << std::endl;
            break;
        }
    }

}
