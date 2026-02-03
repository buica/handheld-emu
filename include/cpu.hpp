#pragma once

#include "common.hpp"
#include "memory.hpp"
#include <atomic>

//to do:
// - read more about z80/8080 cpu architecture
// - implement constants
// - implement isa gradually, high priority opcodes first
// - use blarg's test roms to test
// - cpu.step()



class CPU {
public:
    CPU();
    void printCPU();

    u8 getA() const;
    u8 getB() const;
    u8 getC() const;
    u8 getD() const;
    u8 getE() const;
    u8 getF() const;
    u8 getH() const;
    u8 getL() const;
    u16 getAF() const;
    u16 getBC() const;
    u16 getDE() const;
    u16 getHL() const;
    u16 getSP() const;
    u16 getPC() const;

    void setA(u8 value);
    void setB(u8 value);
    void setC(u8 value);
    void setD(u8 value);
    void setE(u8 value);
    void setF(u8 value);
    void setH(u8 value);
    void setL(u8 value);
    void setAF(u16 value);
    void setBC(u16 value);
    void setDE(u16 value);
    void setHL(u16 value);
    void setSP(u16 value);
    void setPC(u16 value);

    void setZeroFlag(bool set);
    void setSubtractionFlag(bool set);
    void setHalfCarryFlag(bool set);
    void setCarryFlag(bool set);

    bool getZeroFlag() const;
    bool getSubtractionFlag() const;
    bool getHalfCarryFlag() const;
    bool getCarryFlag() const;

    void set_Flags_INC_r8(u8 old_val, u8 new_val);

private:
    void initRegisters();
    u8 fetchInstruction(Memory& memory);
    // void decodeInstruction();
    void executeInstruction(Memory& memory);
    void NOP();
    void LD_BC_n16(Memory& memory);
    void LD_mBC_A(Memory& memory);
    void INC_BC();
    void INC_B();
    void DEC_B();
    void LD_B_n8(Memory& memory);
    void RLCA();
    void LD_mn16_SP(Memory& memory);
    void ADD_HL_BC();
    void LD_A_mBC(Memory& memory);
    void DEC_BC();
    void INC_C();
    void DEC_C();
    void LD_C_n8(Memory& memory);
    void RRCA();
    void STOP();
    void LD_DE_n16(Memory& memory);
    void LD_mDE_A(Memory& memory);
    void INC_DE();
    void INC_D();
    void DEC_D();
    void LD_D_n8(Memory& memory);
    void RLA();
    void JR_e8(Memory& memory);
    void ADD_HL_DE();
    void LD_A_mDE(Memory& memory);
    void DEC_DE();
    void INC_E();
    void DEC_E();
    void LD_E_n8(Memory& memory);
    void RRA();
    void JR_NZ_e8(Memory& memory);
    void LD_HL_n16(Memory& memory);
    void LD_mHLinc_A(Memory& memory);
    void INC_HL();
    void INC_H();
    void DEC_H();
    void LD_H_n8(Memory& memory);
    void DAA();
    void JR_Z_e8(Memory& memory);
    void ADD_HL_HL();
    void LD_A_mHLinc(Memory& memory);
    void DEC_HL();
    void INC_L();
    void DEC_L();
    void LD_L_n8(Memory& memory);
    void CPL();
    void JR_NC_e8(Memory& memory);
    void LD_SP_n16(Memory& memory);
    void LD_mHLdec_A(Memory& memory);
    void INC_SP();
    void INC_mHL(Memory& memory);
    void DEC_mHL(Memory& memory);
    void LD_mHL_n8(Memory& memory);
    void SCF();
    void JR_C_e8(Memory& memory);
    void ADD_HL_SP();
    void LD_A_mHLdec(Memory& memory);
    void DEC_SP();
    void INC_A();
    void DEC_A();
    void LD_A_n8(Memory& memory);
    void CCF();
    void LD_B_B();
    void LD_B_C();
    void LD_B_D();
    void LD_B_E();
    void LD_B_H();
    void LD_B_L();
    void LD_B_mHL(Memory& memory);
    void LD_B_A();
    void LD_C_B();
    void LD_C_C();
    void LD_C_D();
    void LD_C_E();
    void LD_C_H();
    void LD_C_L();
    void LD_C_mHL(Memory& memory);
    void LD_C_A();
    void LD_D_B();
    void LD_D_C();
    void LD_D_D();
    void LD_D_E();
    void LD_D_H();
    void LD_D_L();
    void LD_D_mHL(Memory& memory);
    void LD_D_A();
    void LD_E_B();
    void LD_E_C();
    void LD_E_D();
    void LD_E_E();
    void LD_E_H();
    void LD_E_L();
    void LD_E_mHL(Memory& memory);
    void LD_E_A();

    void HALT();

    void RET();


    u8 m_A;
    u8 m_B;
    u8 m_C;
    u8 m_D;
    u8 m_E;
    u8 m_F;
    u8 m_H;
    u8 m_L;

    u16 m_SP;
    u16 m_PC;
    u8 m_cycles;
};
