#include "../include/cpu.hpp"


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

//these should be within CPU class

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
