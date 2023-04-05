#ifndef CPU_HPP
#define CPU_HPP

#include "common.hpp"
struct CpuRegisters
{
   uint8_t a; // accumulator
   uint8_t b;
   uint8_t c;
   uint8_t d;
   uint8_t e;
   uint8_t h;
   uint8_t l;
   uint16_t sp; // stack pointer
   uint16_t pc; // program counter
};

// todos:
// add cpu instruction set
// add cpu flags
// implement cpu fetch/execute cycle
//

#endif