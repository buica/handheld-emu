#include "../include/cpu.hpp"
#include "../include/memory.hpp"
#include <iostream>


CPU::CPU() {
    // set to boot values
    regAF.AF = 0x0000;
    regBC.BC = 0x0000;
    regDE.DE = 0x0000;
    regHL.HL = 0x0000;
    SP = 0x0000;
    PC = 0x0000;
}

// quick reference access for early debugging
u8& CPU::getA() {
    return regAF.A;
}
u8& CPU::getF() {
    return regAF.F;
}
u16& CPU::getAF() {
    return regAF.AF;
}


u8 CPU::fetchInstruction(Memory& memory) {
    // get the opcode and increment PC
    u8 opcode = memory.readByte(PC++);
    return opcode;
}

void CPU::executeInstruction(Memory& memory) {
    // todo
    // std::cout << "executeInstruction needs to be implemented" << std::endl;
    u8 opcode = fetchInstruction(memory);

    // decode and execute
    // Build up most essential instructions first
    // use opcode tables
    switch(opcode) {
        case 0x00: // NOP
            // 1 byte, 4 cycles
            break;
        case 0x01: // LD BC, n16
            regBC.BC = memory.readWord(PC);
            PC += 2;
            break;

        //...
        case 0x10: // STOP n8
            // 2 bytes, 4 cycles
            PC++;
            break;
            // read more about STOP instruction:
            // https://gbdev.io/pandocs/Reducing_Power_Consumption.html#using-the-stop-instruction


        default:
            std::cerr << "Opcode Not Yet Implemented: 0x" << std::hex << (int)opcode << std::endl;
            break;
    }

    // execute
    //
    //
}



// void cpuInit()
// {
//     // todo
//     std::cout << "cpuInit needs to be implemented" << std::endl;
// }

// bool cpuStep()
// {
//     std::cout << "cpuStep needs to be implemented" << std::endl;
//     return false;
// }
