#pragma once

#include "common.hpp"


///TODO:
// Start	End	First appeared	Purpose
// $FF00		DMG	Joypad input
// $FF01	$FF02	DMG	Serial transfer
// $FF04	$FF07	DMG	Timer and divider
// $FF0F		DMG	Interrupts
// $FF10	$FF26	DMG	Audio
// $FF30	$FF3F	DMG	Wave pattern
// $FF40	$FF4B	DMG	LCD Control, Status, Position, Scrolling, and Palettes
// $FF4F		CGB	VRAM Bank Select
// $FF50		DMG	Boot ROM mapping control
// $FF51	$FF55	CGB	VRAM DMA
// $FF68	$FF6B	CGB	BG / OBJ Palettes
// $FF70		CGB	WRAM Bank Select

constexpr u16 JOYP = 0xFF00; // joypad P1/JOYP
constexpr u16 SB   = 0xFF01; // serial transfer data
constexpr u16 SC   = 0xFF02; // serial transfer control
constexpr u16 DIV  = 0xFF04; // divider register
constexpr u16 TIMA = 0xFF05; // timer counter
constexpr u16 TMA  = 0xFF06; // timer modulo
constexpr u16 TAC  = 0xFF07; // timer control


class IORegisters {
public:
    IORegisters();
        u8 readByte(u16 address);
        void writeByte(u16 address, u8 value);

private:

};
