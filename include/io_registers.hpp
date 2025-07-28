#ifndef IO_REGISTERS_HPP
#define IO_REGISTERS_HPP

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


class IORegisters {
public:
    IORegisters();

private:

};

#endif
