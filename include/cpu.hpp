#ifndef CPU_HPP
#define CPU_HPP

#include "common.hpp"
struct CpuRegisters
{
   u8 a; // accumulator
   u8 b;
   u8 c;
   u8 d;
   u8 e;
   u8 h;
   u8 l;
   u16 sp; // stack pointer
   u16 pc; // program counter
};

// todos:
// add z80 cpu instruction set
// add cpu flags
// implement cpu fetch/decode/execute cycle


#endif