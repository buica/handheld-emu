#include "../include/cpu.hpp"
#include "../include/memory.hpp"
#include <iostream>


CPU::CPU() {
    initRegisters();
}

/*
 * @brief
 * @param
 * @return
 */
void CPU::printCPU() {
    std::clog << "CPU State:" << std::endl;
    std::clog << "AF: " << std::hex << getAF() << std::endl;
    std::clog << "BC: " << std::hex << getBC() << std::endl;
    std::clog << "DE: " << std::hex << getDE() << std::endl;
    std::clog << "HL: " << std::hex << getHL() << std::endl;
    std::clog << "SP: " << std::hex << getSP() << std::endl;
    std::clog << "PC: " << std::hex << getPC() << std::endl;
}

// void CPU::reset() {
//     // set to boot values
// }

/*
 * @brief getters for the registers
 *
 * @return
 */
u8 CPU::getA() const {
    return m_A;
}

u8 CPU::getB() const {
    return m_B;
}

u8 CPU::getC() const {
    return m_C;
}

u8 CPU::getD() const {
    return m_D;
}

u8 CPU::getE() const {
    return m_E;
}

u8 CPU::getF() const {
    return m_F;
}

u8 CPU::getH() const {
    return m_H;
}

u8 CPU::getL() const {
    return m_L;
}

u16 CPU::getAF() const {
    return (static_cast<u16>(m_A) << 8) | m_F;
}

u16 CPU::getBC() const {
    return (static_cast<u16>(m_B) << 8) | m_C;
}

u16 CPU::getDE() const {
    return (static_cast<u16>(m_D) << 8) | m_E;
}

u16 CPU::getHL() const {
    return (static_cast<u16>(m_H) << 8) | m_L;
}

u16 CPU::getSP() const {
    return m_SP;
}

u16 CPU::getPC() const {
    return m_PC;
}

/*
 * Initialize registers to boot values WIP
 */
void CPU::initRegisters() {
    regAF.AF = 0x0000;
    regBC.BC = 0x0000;
    regDE.DE = 0x0000;
    regHL.HL = 0x0000;
    m_SP = 0x0000;
    m_PC = 0x0100; // our emu doesnt care about boot ROM sequence, start game ROM
}

/*
 * @brief
 * @param
 * @return
 */
u8 CPU::fetchInstruction(Memory& memory) {
    // get the opcode and increment PC
    u8 opcode = memory.readByte(m_PC++);
    return opcode;
}

/*
 * @brief
 * @param
 * @return
 */
void CPU::executeInstruction(Memory& memory) {
    // todo
    // std::cout << "executeInstruction needs to be implemented" << std::endl;
    u8 opcode = fetchInstruction(memory);

    /*
     * Should we abstract the instruction decoding into its own method later?
     * Theres way over 100 instructions
     */
    // decode and execute
    // Build up most essential instructions first
    // use opcode tables
    switch(opcode) {
        case 0x00: // NOP
        {
            // 1 byte, 4 cycles
            break;
        }
        case 0x01: // LD BC, n16
        {
            u16 val = memory.readWord(m_PC);
            m_B = val >> 8;
            m_C = val & 0xFF;
            m_PC += 2;
            break;
        }

        //...
        case 0x10: // STOP n8
        {
            // 2 bytes, 4 cycles
            m_PC++;
            break;
            // read more about STOP instruction:
            // https://gbdev.io/pandocs/Reducing_Power_Consumption.html#using-the-stop-instruction
        }

        default:
        {
            std::cerr << "Opcode Not Yet Implemented: 0x" << std::hex << (int)opcode << std::endl;
            break;
        }
    }

}
