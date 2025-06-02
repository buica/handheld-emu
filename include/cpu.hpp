#ifndef CPU_HPP
#define CPU_HPP

#include "common.hpp"

//to do:
// read more about z80/8080 cpu architecture
// implement constants
// implement isa gradually, high priority opcodes first
// use blarg's test roms to test


class CPU {
public:


private:
   u8 regA; // accumulator
   u8 regB;
   u8 regC;
   u8 regD;
   u8 regE;
   u8 regH;
   u8 regL;
   u16 stackPtr;
   u16 progCounter;


// todos:
// add z80 cpu instruction set
// add cpu flags
// implement cpu fetch/decode/execute cycle

};
#endif
