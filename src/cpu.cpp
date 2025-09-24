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
u16 CPU::getAF() const { return (static_cast<u16>(m_A) << 8) | m_F; }
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
    // todo
    // std::cout << "executeInstruction needs to be implemented" << std::endl;
    u8 opcode = fetchInstruction(memory);

    // decode and execute
    // Build up most essential instructions first
    // use opcode tables
    switch(opcode) {
        // NOP
        case 0x00: {
            // 1 byte (PC+1), 4 cycles
            break;
        }
        // LD BC, n16: Load 16-bit immediate into BC
        case 0x01: {
            u16 val = memory.readWord(m_PC);
            m_B = val >> 8;
            m_C = val & 0xFF;
            m_PC += 2;
            break;
        }
        // STOP
        case 0x10: {
            // 2 bytes, 4 cycles
            m_PC++;
            break;
            // read more about STOP instruction:
            // https://gbdev.io/pandocs/Reducing_Power_Consumption.html#using-the-stop-instruction
        }
        // HALT
        case 0x76:



        default: {
            std::cerr << "Opcode Not Yet Implemented: 0x" << std::hex << (int)opcode << std::endl;
            break;
        }
    }

}
