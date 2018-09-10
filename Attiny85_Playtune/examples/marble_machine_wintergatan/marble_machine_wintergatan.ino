/*
this is a modified version of the menorah of LenShustek (the same creator of playtune) https://github.com/LenShustek/ATtiny-playtune .
it has been modified by David Rubio https://github.com/theawsomeavr https://www.youtube.com/channel/UCLe_nq4scjhtKgyudTweZMQ
to be compatible with the popular attiny85 in 08/09/2018.
it uses timer0 for toggling the 3 pins for generating squarewaves and timer1 for changing the note
to play next in each squarewave generator, this library support the attiny85 at 16 or 8 mhz.
for creating custom files you will need miditones (a LenShustek midi to c comverter) that you can download from
here https://code.google.com/archive/p/miditones/downloads
how you use it is the folowing:
(download miditonesV1.4.exe for 32 bit systems or V1.6 for 64 bit)
this program needs to be executed from cmd so open it
go to the directory using cd commands and put the following command
"miditonesV1.4 (or name of the exe file)" -t3 "(name of the midi file)"
*/


#include <Attiny85_Playtune.h>

//-----------------------------------------------------------------------------------------------------
// The music we play, generated by "miditones" from MIDI files.
//-----------------------------------------------------------------------------------------------------

/// Playtune bytestream for file "marblemachine.mid" created by MIDITONES V1.4 on Sat Sep  8 17:39:30 2018

const byte PROGMEM score [] = {
0x90,0x58, 0,204, 0x80, 0,204, 0x90,0x47, 0x91,0x4C, 0,204, 0x80, 0x81, 0x90,0x53, 0,204, 0x80, 1,152, 
0x90,0x47, 0x91,0x4C, 0,204, 0x80, 0x81, 0x90,0x51, 0,204, 0x80, 0x90,0x4F, 0,204, 0x80, 0x90,0x51, 0,204, 
0x80, 0x90,0x47, 0x91,0x4C, 0,204, 0x81, 0x80, 0x90,0x53, 0,204, 0x80, 0,204, 0x90,0x4F, 0,204, 0x80, 
0x90,0x4C, 0x91,0x47, 0x92,0x51, 0,204, 0x82, 0x80, 0x81, 0x90,0x56, 0,204, 0x80, 1,152, 0x90,0x4A, 0x91,0x47, 
0,204, 0x80, 0x81, 0x90,0x53, 0,204, 0x80, 1,152, 0x90,0x4A, 0x91,0x47, 0,204, 0x80, 0x81, 0x90,0x51, 
0,204, 0x80, 0x90,0x4F, 0,204, 0x80, 0x90,0x51, 0,204, 0x80, 0x90,0x47, 0x91,0x4A, 0,204, 0x81, 0x80, 
0x90,0x4E, 0,204, 0x80, 0,204, 0x90,0x4F, 0,204, 0x80, 0x90,0x47, 0x91,0x4A, 0x92,0x51, 0,204, 0x82, 
0x80, 0x81, 0x90,0x56, 0,204, 0x80, 1,152, 0x90,0x4A, 0x91,0x4E, 0,204, 0x80, 0x81, 0x90,0x53, 0,204, 
0x80, 1,152, 0x90,0x4A, 0x91,0x4E, 0,204, 0x80, 0x81, 0x90,0x56, 0,204, 0x80, 0x90,0x54, 0,204, 0x80, 
0x90,0x53, 0,204, 0x80, 0x90,0x4A, 0x91,0x4E, 0,204, 0x81, 0x80, 0x90,0x51, 0,204, 0x80, 0,204, 0x90,0x4F, 
0,204, 0x80, 0x90,0x51, 0x91,0x4A, 0x92,0x4E, 0,204, 0x82, 0x80, 0x81, 0x90,0x4C, 0,204, 0x80, 0,204, 
0x90,0x48, 0,204, 0x80, 0x90,0x4C, 0,204, 0x80, 0x90,0x53, 0,204, 0x80, 0x90,0x47, 0,204, 0x80, 0x90,0x48, 
0,204, 0x80, 0x90,0x4A, 0,204, 0x80, 0x90,0x56, 0,204, 0x80, 0x90,0x54, 0,204, 0x80, 0x90,0x53, 0,204, 
0x80, 0x90,0x4A, 0x91,0x4E, 0,204, 0x81, 0x80, 0x90,0x51, 0,204, 0x80, 0,204, 0x90,0x4F, 0,204, 0x80, 
0x90,0x4A, 0x91,0x4E, 0x92,0x51, 0,204, 0x82, 0x80, 0x81, 0x90,0x58, 0,204, 0x80, 1,152, 0x90,0x47, 0x91,0x4C, 
0,204, 0x80, 0x81, 0x90,0x53, 0,204, 0x80, 1,152, 0x90,0x47, 0x91,0x4C, 0,204, 0x80, 0x81, 0x90,0x51, 
0,204, 0x80, 0x90,0x4F, 0,204, 0x80, 0x90,0x51, 0,204, 0x80, 0x90,0x47, 0x91,0x4C, 0,204, 0x81, 0x80, 
0x90,0x53, 0,204, 0x80, 0,204, 0x90,0x4F, 0,204, 0x80, 0x90,0x4C, 0x91,0x47, 0x92,0x51, 0,204, 0x82, 
0x80, 0x81, 0x90,0x56, 0,204, 0x80, 1,152, 0x90,0x4A, 0x91,0x47, 0,204, 0x80, 0x81, 0x90,0x53, 0,204, 
0x80, 1,152, 0x90,0x4A, 0x91,0x47, 0,204, 0x80, 0x81, 0x90,0x56, 0,204, 0x80, 0x90,0x54, 0,204, 0x80, 
0x90,0x53, 0,204, 0x80, 0x90,0x4A, 0x91,0x47, 0,204, 0x81, 0x80, 0x90,0x51, 0,204, 0x80, 0,204, 0x90,0x4F, 
0,204, 0x80, 0x90,0x51, 0x91,0x47, 0x92,0x4A, 0,204, 0x82, 0x80, 0x81, 0x90,0x56, 0,204, 0x80, 1,152, 
0x90,0x4A, 0x91,0x4E, 0,204, 0x80, 0x81, 0x90,0x53, 0,204, 0x80, 1,152, 0x90,0x51, 0x91,0x4E, 0x92,0x4A, 
0,204, 0x80, 0x81, 0x82, 0x90,0x58, 0,204, 0x80, 0,204, 0x90,0x53, 0,204, 0x80, 0x90,0x47, 0x91,0x4A, 
0,204, 0x81, 0x80, 0x90,0x51, 0,204, 0x80, 0,204, 0x90,0x4F, 0,204, 0x80, 0x90,0x47, 0x91,0x4A, 0x92,0x4E, 
0,204, 0x82, 0x80, 0x81, 0x90,0x4C, 0,204, 0x80, 0,204, 0x90,0x47, 0,204, 0x80, 0x90,0x48, 0,204, 
0x80, 0x90,0x4E, 0,204, 0x80, 0x90,0x48, 0,204, 0x80, 0x90,0x4C, 0,204, 0x80, 0x90,0x4F, 0,204, 0x80, 
0x90,0x4A, 0,204, 0x80, 0x90,0x4E, 0,204, 0x80, 0x90,0x51, 0,204, 0x80, 0x90,0x47, 0,204, 0x80, 0x90,0x53, 
0,204, 0x80, 0x90,0x4A, 0,204, 0x80, 0x90,0x4F, 0,204, 0x80, 0x90,0x51, 0,204, 0x80, 0x90,0x58, 0,204, 
0x91,0x1C, 0x80, 0,204, 0x81, 0,204, 0x90,0x47, 0x91,0x28, 0x92,0x4C, 0,204, 0x81, 0x80, 0x82, 0x90,0x53, 
0,204, 0x91,0x34, 0x80, 0,204, 0x81, 0x90,0x28, 0,204, 0x91,0x47, 0x80, 0x90,0x4C, 0,204, 0x92,0x40, 
0x80, 0x81, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x28, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x1C, 0x91,0x51, 0,204, 
0x80, 0x81, 0x90,0x47, 0x91,0x4C, 0,204, 0x81, 0x80, 0x90,0x53, 0,204, 0x91,0x2B, 0x80, 0,204, 0x81, 0x90,0x4F, 
0x91,0x2D, 0,204, 0x80, 0x81, 0x90,0x4C, 0x91,0x2F, 0x92,0x47, 0,204, 0x81, 0x82, 0x80, 0x90,0x32, 0x91,0x56, 
0,204, 0x80, 0x81, 0,204, 0x90,0x2B, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0x92,0x1F, 0,204, 0x80, 0x81, 
0x82, 0x90,0x53, 0,204, 0x91,0x2B, 0x80, 0,204, 0x81, 0x90,0x1F, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0,204, 
0x92,0x3E, 0x80, 0x81, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x4F, 0,204, 0x91,0x37, 0x80, 0x90,0x51, 0,204, 
0x81, 0x80, 0x90,0x47, 0x91,0x4A, 0,204, 0x92,0x2B, 0x81, 0x80, 0x90,0x4E, 0,204, 0x82, 0x80, 0x90,0x2A, 0,204, 
0x91,0x4F, 0x80, 0x90,0x2B, 0,204, 0x81, 0x80, 0x90,0x47, 0x91,0x2D, 0x92,0x4A, 0,204, 0x81, 0x82, 0x80, 0x90,0x32, 
0x91,0x56, 0,204, 0x80, 0x81, 0x90,0x23, 0,204, 0x80, 0,204, 0x90,0x4A, 0x91,0x23, 0x92,0x4E, 0,204, 
0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x2F, 0x80, 0,204, 0x81, 0x90,0x23, 0,204, 0x91,0x4A, 0x80, 0x90,0x4E, 
0,204, 0x92,0x23, 0x80, 0x81, 0x90,0x56, 0,204, 0x82, 0x80, 0x90,0x2F, 0x91,0x54, 0,204, 0x80, 0x81, 0x90,0x23, 
0x91,0x53, 0,204, 0x80, 0x81, 0x90,0x4A, 0x91,0x4E, 0,204, 0x92,0x2F, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 
0x80, 0x90,0x2F, 0,204, 0x91,0x4F, 0x80, 0x90,0x23, 0,204, 0x81, 0x80, 0x90,0x51, 0x91,0x26, 0x92,0x4A, 0,204, 
0x81, 0x82, 0x80, 0x90,0x28, 0x91,0x4C, 0,204, 0x80, 0x81, 0x90,0x24, 0,204, 0x91,0x48, 0,204, 0x81, 0x91,0x4C, 
0,204, 0x81, 0x91,0x53, 0,204, 0x80, 0x81, 0x90,0x30, 0x91,0x47, 0,204, 0x81, 0x91,0x48, 0,204, 0x81, 
0x91,0x4A, 0,204, 0x81, 0x91,0x56, 0,204, 0x80, 0x81, 0x90,0x26, 0x91,0x54, 0,204, 0x81, 0x91,0x53, 0,204, 
0x80, 0x81, 0x90,0x4A, 0x91,0x4E, 0,204, 0x92,0x32, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0,204, 0x90,0x4F, 
0,204, 0x91,0x34, 0x80, 0x90,0x4A, 0x92,0x4E, 0,204, 0x80, 0x82, 0x90,0x58, 0,204, 0x81, 0x80, 0x90,0x1C, 
0,204, 0x80, 0,204, 0x90,0x47, 0x91,0x28, 0x92,0x4C, 0,204, 0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x34, 
0x80, 0,204, 0x81, 0x90,0x1C, 0,204, 0x91,0x47, 0x80, 0x90,0x4C, 0,204, 0x92,0x40, 0x80, 0x81, 0x90,0x51, 
0,204, 0x82, 0x80, 0x90,0x4F, 0,204, 0x91,0x34, 0x80, 0x90,0x51, 0,204, 0x81, 0x80, 0x90,0x47, 0x91,0x4C, 
0,204, 0x81, 0x80, 0x90,0x53, 0,204, 0x91,0x28, 0x80, 0,204, 0x81, 0x90,0x4F, 0x91,0x2B, 0,204, 0x80, 
0x81, 0x90,0x4C, 0x91,0x2D, 0x92,0x47, 0,204, 0x81, 0x82, 0x80, 0x90,0x32, 0x91,0x56, 0,204, 0x80, 0x81, 0,204, 
0x90,0x2B, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0x92,0x1F, 0,204, 0x80, 0x81, 0x82, 0x90,0x53, 0,204, 0x91,0x2B, 
0x80, 0,204, 0x81, 0x90,0x1F, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0,204, 0x92,0x3E, 0x80, 0x81, 0x90,0x56, 
0,204, 0x82, 0x80, 0x90,0x54, 0,204, 0x91,0x37, 0x80, 0x90,0x53, 0,204, 0x81, 0x80, 0x90,0x4A, 0x91,0x47, 
0,204, 0x92,0x2B, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x2A, 0,204, 0x91,0x4F, 0x80, 0x90,0x2B, 
0,204, 0x81, 0x80, 0x90,0x51, 0x91,0x2D, 0x92,0x47, 0,204, 0x81, 0x82, 0x80, 0x90,0x32, 0x91,0x56, 0,204, 
0x80, 0x81, 0x90,0x23, 0,204, 0x80, 0,204, 0x90,0x4A, 0x91,0x23, 0x92,0x4E, 0,204, 0x81, 0x80, 0x82, 0x90,0x53, 
0,204, 0x91,0x2F, 0x80, 0,204, 0x81, 0x90,0x23, 0,204, 0x91,0x51, 0x80, 0x90,0x4E, 0x92,0x4A, 0,204, 
0x82, 0x81, 0x80, 0x90,0x58, 0,204, 0x80, 0x90,0x2F, 0,204, 0x91,0x53, 0x80, 0x90,0x23, 0,204, 0x81, 0x80, 
0x90,0x47, 0x91,0x4A, 0,204, 0x92,0x2D, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0,204, 0x90,0x2B, 0x91,0x4F, 
0,204, 0x80, 0x81, 0x90,0x2A, 0x91,0x47, 0x92,0x4A, 0,204, 0x82, 0x81, 0x91,0x4C, 0,204, 0x80, 0x81, 0x90,0x21, 
0,204, 0x91,0x47, 0,204, 0x81, 0x91,0x48, 0,204, 0x81, 0x91,0x4E, 0,204, 0x80, 0x81, 0x90,0x2D, 0x91,0x48, 
0,204, 0x80, 0x81, 0x90,0x21, 0x91,0x4C, 0,204, 0x81, 0x91,0x4F, 0,204, 0x81, 0x91,0x4A, 0,204, 0x80, 
0x81, 0x90,0x23, 0x91,0x4E, 0,204, 0x81, 0x91,0x51, 0,204, 0x81, 0x91,0x47, 0,204, 0x80, 0x81, 0x90,0x2F, 
0x91,0x53, 0,204, 0x81, 0x91,0x4A, 0,204, 0x81, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x23, 0x91,0x51, 0,204, 
0x81, 0x91,0x58, 0,204, 0x80, 0x81, 0x90,0x24, 0,204, 0x80, 0,204, 0x90,0x47, 0x91,0x24, 0x92,0x4C, 0,204, 
0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x30, 0x80, 0,204, 0x81, 0x90,0x24, 0,204, 0x91,0x47, 0x80, 0x90,0x4C, 
0,204, 0x92,0x24, 0x80, 0x81, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x30, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x24, 
0x91,0x51, 0,204, 0x80, 0x81, 0x90,0x47, 0x91,0x4C, 0,204, 0x92,0x30, 0x81, 0x80, 0x90,0x53, 0,204, 0x82, 
0x80, 0,204, 0x90,0x2B, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x2D, 0x91,0x4C, 0x92,0x47, 0,204, 0x80, 0x82, 
0x81, 0x90,0x32, 0x91,0x56, 0,204, 0x80, 0x81, 0,204, 0x90,0x32, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0x92,0x26, 
0,204, 0x80, 0x81, 0x82, 0x90,0x53, 0,204, 0x91,0x32, 0x80, 0,204, 0x81, 0x90,0x26, 0,204, 0x91,0x4A, 
0x80, 0x90,0x47, 0,204, 0x92,0x3E, 0x80, 0x81, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x4F, 0,204, 0x91,0x32, 
0x80, 0x90,0x51, 0,204, 0x81, 0x80, 0x90,0x47, 0x91,0x4A, 0,204, 0x92,0x3B, 0x81, 0x80, 0x90,0x4E, 0,204, 
0x82, 0x80, 0,204, 0x90,0x37, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x39, 0x91,0x47, 0x92,0x4A, 0,204, 0x80, 
0x82, 0x81, 0x90,0x3E, 0x91,0x56, 0,204, 0x80, 0x81, 0x90,0x1C, 0,204, 0x80, 0,204, 0x90,0x4A, 0x91,0x28, 
0x92,0x4E, 0,204, 0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x34, 0x80, 0,204, 0x81, 0x90,0x28, 0,204, 
0x91,0x4A, 0x80, 0x90,0x4E, 0,204, 0x92,0x1C, 0x80, 0x81, 0x90,0x56, 0,204, 0x82, 0x80, 0x90,0x34, 0x91,0x54, 
0,204, 0x80, 0x81, 0x90,0x28, 0x91,0x53, 0,204, 0x80, 0x81, 0x90,0x4A, 0x91,0x4E, 0,204, 0x92,0x1C, 0x81, 
0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0,204, 0x90,0x28, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x2B, 0x91,0x51, 
0x92,0x4A, 0,204, 0x82, 0x81, 0x91,0x4C, 0,204, 0x80, 0x81, 0x90,0x21, 0,204, 0x91,0x48, 0,204, 0x81, 
0x91,0x4C, 0,204, 0x81, 0x91,0x53, 0,204, 0x80, 0x81, 0x90,0x2D, 0x91,0x47, 0,204, 0x80, 0x81, 0x90,0x21, 
0x91,0x48, 0,204, 0x81, 0x91,0x4A, 0,204, 0x81, 0x91,0x56, 0,204, 0x80, 0x81, 0x90,0x23, 0x91,0x54, 0,204, 
0x81, 0x91,0x53, 0,204, 0x81, 0x91,0x4A, 0x92,0x4E, 0,204, 0x80, 0x82, 0x81, 0x90,0x2F, 0x91,0x51, 0,204, 
0x81, 0,204, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x23, 0x91,0x4A, 0x92,0x4E, 0,204, 0x82, 0x81, 0x91,0x58, 
0,204, 0x80, 0x81, 0x90,0x24, 0,204, 0x80, 0,204, 0x90,0x47, 0x91,0x24, 0x92,0x4C, 0,204, 0x81, 0x80, 
0x82, 0x90,0x53, 0,204, 0x91,0x30, 0x80, 0,204, 0x81, 0x90,0x24, 0,204, 0x91,0x47, 0x80, 0x90,0x4C, 0,204, 
0x92,0x24, 0x80, 0x81, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x30, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x24, 0x91,0x51, 
0,204, 0x80, 0x81, 0x90,0x47, 0x91,0x4C, 0,204, 0x92,0x30, 0x81, 0x80, 0x90,0x53, 0,204, 0x82, 0x80, 0,204, 
0x90,0x2B, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x2D, 0x91,0x4C, 0x92,0x47, 0,204, 0x80, 0x82, 0x81, 0x90,0x32, 
0x91,0x56, 0,204, 0x80, 0x81, 0,204, 0x90,0x32, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0x92,0x26, 0,204, 
0x80, 0x81, 0x82, 0x90,0x53, 0,204, 0x91,0x32, 0x80, 0,204, 0x81, 0x90,0x26, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 
0,204, 0x92,0x3E, 0x80, 0x81, 0x90,0x56, 0,204, 0x82, 0x80, 0x90,0x54, 0,204, 0x91,0x3C, 0x80, 0x90,0x53, 
0,204, 0x81, 0x80, 0x90,0x4A, 0x91,0x47, 0,204, 0x92,0x3B, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x26, 
0,204, 0x91,0x4F, 0x80, 0x90,0x2B, 0,204, 0x81, 0x80, 0x90,0x51, 0x91,0x2D, 0x92,0x47, 0,204, 0x81, 0x82, 
0x80, 0x90,0x32, 0x91,0x56, 0,204, 0x80, 0x81, 0x90,0x28, 0,204, 0x80, 0,204, 0x90,0x4A, 0x91,0x28, 0x92,0x4E, 
0,204, 0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x34, 0x80, 0,204, 0x81, 0x90,0x28, 0,204, 0x91,0x51, 
0x80, 0x90,0x4E, 0x92,0x4A, 0,204, 0x82, 0x81, 0x80, 0x90,0x58, 0,204, 0x80, 0x90,0x34, 0,204, 0x91,0x53, 
0x80, 0x90,0x28, 0,204, 0x81, 0x80, 0x90,0x47, 0x91,0x4A, 0,204, 0x92,0x28, 0x81, 0x80, 0x90,0x51, 0,204, 
0x82, 0x80, 0,204, 0x90,0x28, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x2B, 0x91,0x47, 0x92,0x4A, 0,204, 0x80, 
0x82, 0x81, 0x90,0x4C, 0,204, 0x91,0x28, 2,100, 0x81, 0x91,0x34, 3,252, 0x80, 6,96, 0x81, 0x90,0x4F, 
0x91,0x58, 12,193, 0x81, 0x80, 0x90,0x56, 0x91,0x4F, 12,193, 0x81, 0x80, 0x90,0x4E, 0x91,0x56, 12,193, 0x81, 
0x80, 0x90,0x54, 0x91,0x4F, 0x92,0x4C, 12,193, 0x82, 0x81, 0x80, 0x90,0x53, 3,48, 0x80, 0x90,0x4C, 0x91,0x58, 
3,48, 0x81, 0x80, 0x90,0x53, 6,96, 0x80, 0x90,0x4A, 0x91,0x56, 3,48, 0x81, 0x80, 0x90,0x53, 6,96, 
0x80, 0x90,0x56, 0x91,0x47, 3,48, 0x81, 0x80, 0x90,0x53, 6,96, 0x80, 0x90,0x51, 1,152, 0x80, 0x90,0x53, 
1,152, 0x80, 0x90,0x48, 1,152, 0x80, 0x90,0x4C, 1,152, 0x80, 0x90,0x48, 0,102, 0x80, 0x90,0x4C, 0,204, 
0x80, 0x90,0x54, 0,102, 0x80, 0x90,0x58, 4,200, 0x80, 6,96, 15,160, 0x90,0x1C, 3,232, 0x80, 0x90,0x28, 
3,232, 0x80, 0x90,0x34, 1,244, 0x80, 0x90,0x1C, 3,232, 0x80, 0x90,0x34, 1,244, 0x80, 0x90,0x28, 1,244, 
0x80, 0x90,0x1F, 1,244, 0x80, 1,244, 0x90,0x34, 1,244, 0x80, 0x90,0x1C, 1,244, 0x80, 0x90,0x1F, 1,244, 
0x80, 0x90,0x28, 1,244, 0x80, 0x90,0x2B, 3,232, 0x80, 0x90,0x2B, 1,244, 0x80, 0x90,0x1F, 1,244, 0x80, 
1,244, 0x90,0x37, 1,244, 0x80, 1,244, 0x90,0x2B, 1,244, 0x80, 0x90,0x21, 1,244, 0x80, 0x90,0x2B, 
1,244, 0x80, 0x90,0x2B, 1,244, 0x80, 0x90,0x21, 1,244, 0x80, 1,244, 0x90,0x1F, 1,244, 0x80, 1,244, 
0x90,0x28, 1,244, 0x80, 0x90,0x1F, 1,244, 0x80, 0x90,0x2B, 1,244, 0x80, 0x90,0x23, 1,244, 0x80, 1,244, 
0x90,0x23, 1,244, 0x80, 1,244, 0x90,0x21, 1,244, 0x80, 0x90,0x23, 1,244, 0x80, 1,244, 0x90,0x21, 
1,244, 0x80, 0x90,0x21, 1,244, 0x80, 0x90,0x23, 1,244, 0x80, 1,244, 0x90,0x23, 1,244, 0x80, 1,244, 
0x90,0x23, 1,244, 0x80, 3,232, 0x90,0x24, 7,208, 0x80, 0x90,0x30, 5,220, 0,204, 0x80, 0x90,0x26, 
2,100, 0x80, 0x90,0x32, 0,204, 0x80, 0,204, 0x90,0x1C, 0,204, 0x80, 0x90,0x28, 0,204, 0x80, 0x90,0x1C, 
0,204, 0x80, 0,204, 0x90,0x28, 0,204, 0x80, 0,204, 0x90,0x34, 0,204, 0x80, 0x90,0x1C, 0,204, 
0x80, 0,204, 0x90,0x40, 0,204, 0x80, 0,204, 0x90,0x34, 0,204, 0x80, 1,152, 0x90,0x28, 0,204, 
0x80, 0x90,0x2B, 0,204, 0x80, 0x90,0x2D, 0,204, 0x80, 0x90,0x32, 0,204, 0x80, 0,204, 0x90,0x2B, 0,204, 
0x80, 0x90,0x1F, 0,204, 0x80, 0,204, 0x90,0x2B, 0,204, 0x80, 0x90,0x1F, 0,204, 0x80, 0,204, 0x90,0x3E, 
0,204, 0x80, 0,204, 0x90,0x37, 0,204, 0x80, 0,204, 0x90,0x2B, 0,204, 0x80, 0x90,0x2A, 0,204, 
0x80, 0x90,0x2B, 0,204, 0x80, 0x90,0x2D, 0,204, 0x80, 0x90,0x32, 0,204, 0x80, 0x90,0x23, 0,204, 0x80, 
0,204, 0x90,0x23, 0,204, 0x80, 0,204, 0x90,0x2F, 0,204, 0x80, 0x90,0x23, 0,204, 0x80, 0,204, 
0x90,0x23, 0,204, 0x80, 0x90,0x2F, 0,204, 0x80, 0x90,0x23, 0,204, 0x80, 0,204, 0x90,0x23, 0,204, 
0x80, 0,204, 0x90,0x23, 0,204, 0x80, 0x90,0x26, 0,204, 0x80, 0x90,0x28, 0,204, 0x80, 0x90,0x1C, 3,48, 
0x80, 0x90,0x2B, 0,204, 0x80, 0x90,0x2B, 5,148, 0x80, 0x90,0x2B, 0,204, 0x80, 0x90,0x1C, 0,204, 0x80, 
0x90,0x1C, 0,204, 0x80, 0x90,0x2B, 0,204, 0x91,0x58, 0x80, 0x90,0x24, 0,204, 0x81, 0x80, 0,204, 0x90,0x47, 
0x91,0x24, 0x92,0x4C, 0,204, 0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x30, 0x80, 0,204, 0x81, 0x90,0x24, 
0,204, 0x91,0x47, 0x80, 0x90,0x4C, 0,204, 0x92,0x24, 0x80, 0x81, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x30, 
0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x24, 0x91,0x51, 0,204, 0x80, 0x81, 0x90,0x47, 0x91,0x4C, 0,204, 0x92,0x30, 
0x81, 0x80, 0x90,0x53, 0,204, 0x82, 0x80, 0,204, 0x90,0x2B, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x2D, 0x91,0x4C, 
0x92,0x47, 0,204, 0x80, 0x82, 0x81, 0x90,0x32, 0x91,0x56, 0,204, 0x80, 0x81, 0,204, 0x90,0x32, 0,204, 
0x91,0x4A, 0x80, 0x90,0x47, 0x92,0x26, 0,204, 0x80, 0x81, 0x82, 0x90,0x53, 0,204, 0x91,0x32, 0x80, 0,204, 
0x81, 0x90,0x26, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0,204, 0x92,0x3E, 0x80, 0x81, 0x90,0x51, 0,204, 0x82, 
0x80, 0x90,0x4F, 0,204, 0x91,0x32, 0x80, 0x90,0x51, 0,204, 0x81, 0x80, 0x90,0x47, 0x91,0x4A, 0,204, 0x92,0x2B, 
0x81, 0x80, 0x90,0x4E, 0,204, 0x82, 0x80, 0x90,0x2A, 0,204, 0x91,0x4F, 0x80, 0x90,0x2B, 0,204, 0x81, 0x80, 
0x90,0x47, 0x91,0x2D, 0x92,0x4A, 0,204, 0x81, 0x82, 0x80, 0x90,0x32, 0x91,0x56, 0,204, 0x80, 0x81, 0x90,0x28, 
0,204, 0x80, 0,204, 0x90,0x4A, 0x91,0x28, 0x92,0x4E, 0,204, 0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x34, 
0x80, 0,204, 0x81, 0x90,0x28, 0,204, 0x91,0x4A, 0x80, 0x90,0x4E, 0,204, 0x92,0x28, 0x80, 0x81, 0x90,0x56, 
0,204, 0x82, 0x80, 0x90,0x34, 0x91,0x54, 0,204, 0x80, 0x81, 0x90,0x28, 0x91,0x53, 0,204, 0x80, 0x81, 0x90,0x4A, 
0x91,0x4E, 0,204, 0x92,0x34, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0,204, 0x90,0x28, 0x91,0x4F, 0,204, 
0x80, 0x81, 0x90,0x2B, 0x91,0x51, 0x92,0x4A, 0,204, 0x80, 0x82, 0x81, 0x90,0x4C, 0,204, 0x91,0x2D, 0x80, 0,204, 
0x90,0x48, 0,204, 0x80, 0x90,0x4C, 0,204, 0x80, 0x90,0x53, 0,204, 0x81, 0x80, 0x90,0x39, 0x91,0x47, 0,204, 
0x81, 0x91,0x48, 0,204, 0x81, 0x91,0x4A, 0,204, 0x81, 0x91,0x56, 0,204, 0x80, 0x81, 0x90,0x2F, 0x91,0x54, 
0,204, 0x81, 0x91,0x53, 0,204, 0x81, 0x91,0x4A, 0x92,0x4E, 0,204, 0x80, 0x82, 0x81, 0x90,0x3B, 0x91,0x51, 
0,204, 0x80, 0x81, 0,204, 0x90,0x1C, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x28, 0x91,0x4A, 0x92,0x4E, 0,204, 
0x80, 0x82, 0x81, 0x90,0x58, 0,204, 0x91,0x24, 0x80, 0,204, 0x81, 0,204, 0x90,0x47, 0x91,0x24, 0x92,0x4C, 
0,204, 0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x30, 0x80, 0,204, 0x81, 0x90,0x24, 0,204, 0x91,0x47, 
0x80, 0x90,0x4C, 0,204, 0x92,0x39, 0x80, 0x81, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x30, 0x91,0x4F, 0,204, 
0x80, 0x81, 0x90,0x1C, 0x91,0x51, 0,204, 0x80, 0x81, 0x90,0x47, 0x91,0x4C, 0,204, 0x92,0x3B, 0x81, 0x80, 0x90,0x53, 
0,204, 0x82, 0x80, 0x90,0x1C, 0,204, 0x91,0x4F, 0x80, 0x90,0x2B, 0,204, 0x81, 0x80, 0x90,0x4C, 0x91,0x2D, 
0x92,0x47, 0,204, 0x81, 0x82, 0x80, 0x90,0x32, 0x91,0x56, 0,204, 0x80, 0x81, 0,204, 0x90,0x32, 0,204, 
0x91,0x4A, 0x80, 0x90,0x47, 0x92,0x26, 0,204, 0x80, 0x81, 0x82, 0x90,0x53, 0,204, 0x91,0x32, 0x80, 0,204, 
0x81, 0x90,0x26, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0,204, 0x92,0x32, 0x80, 0x81, 0x90,0x56, 0,204, 0x82, 
0x80, 0x90,0x54, 0,204, 0x91,0x30, 0x80, 0x90,0x53, 0,204, 0x81, 0x80, 0x90,0x4A, 0x91,0x47, 0,204, 0x92,0x2F, 
0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x1C, 0,204, 0x91,0x4F, 0x80, 0x90,0x37, 0,204, 0x81, 0x80, 
0x90,0x51, 0x91,0x39, 0x92,0x47, 0,204, 0x81, 0x82, 0x80, 0x90,0x3E, 0x91,0x56, 0,204, 0x80, 0x81, 0x90,0x28, 
0,204, 0x80, 0,204, 0x90,0x4A, 0x91,0x28, 0x92,0x4E, 0,204, 0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x34, 
0x80, 0,204, 0x81, 0x90,0x28, 0,204, 0x91,0x51, 0x80, 0x90,0x4E, 0x92,0x4A, 0,204, 0x82, 0x81, 0x80, 0x90,0x58, 
0,204, 0x80, 0x90,0x1F, 0,204, 0x91,0x53, 0x80, 0x90,0x28, 0,204, 0x81, 0x80, 0x90,0x47, 0x91,0x4A, 0,204, 
0x92,0x40, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0,204, 0x90,0x28, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x47, 
0x91,0x4A, 0x92,0x4E, 0,204, 0x82, 0x81, 0x80, 0x90,0x4C, 7,44, 0x80, 6,96, 0x90,0x1C, 0x91,0x58, 0,204, 
0x80, 0x81, 0,204, 0x90,0x28, 0x91,0x47, 0x92,0x4C, 0,204, 0x80, 0x81, 0x82, 0x90,0x53, 0,204, 0x91,0x34, 
0x80, 0,204, 0x81, 0x90,0x28, 0,204, 0x91,0x47, 0x80, 0x90,0x4C, 0,204, 0x92,0x40, 0x80, 0x81, 0x90,0x51, 
0,204, 0x82, 0x80, 0x90,0x28, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x1C, 0x91,0x51, 0,204, 0x80, 0x81, 0x90,0x47, 
0x91,0x4C, 0,204, 0x81, 0x80, 0x90,0x53, 0,204, 0x91,0x2B, 0x80, 0,204, 0x81, 0x90,0x4F, 0x91,0x2D, 0,204, 
0x80, 0x81, 0x90,0x4C, 0x91,0x2F, 0x92,0x47, 0,204, 0x81, 0x82, 0x80, 0x90,0x32, 0x91,0x56, 0,204, 0x80, 0x81, 
0,204, 0x90,0x2B, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0x92,0x1F, 0,204, 0x80, 0x81, 0x82, 0x90,0x53, 0,204, 
0x91,0x2B, 0x80, 0,204, 0x81, 0x90,0x1F, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0,204, 0x92,0x3E, 0x80, 0x81, 
0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x4F, 0,204, 0x91,0x37, 0x80, 0x90,0x51, 0,204, 0x81, 0x80, 0x90,0x47, 
0x91,0x4A, 0,204, 0x92,0x2B, 0x81, 0x80, 0x90,0x4E, 0,204, 0x82, 0x80, 0x90,0x2A, 0,204, 0x91,0x4F, 0x80, 
0x90,0x2B, 0,204, 0x81, 0x80, 0x90,0x47, 0x91,0x2D, 0x92,0x4A, 0,204, 0x81, 0x82, 0x80, 0x90,0x32, 0x91,0x56, 
0,204, 0x80, 0x81, 0x90,0x23, 0,204, 0x80, 0,204, 0x90,0x4A, 0x91,0x23, 0x92,0x4E, 0,204, 0x81, 0x80, 
0x82, 0x90,0x53, 0,204, 0x91,0x2F, 0x80, 0,204, 0x81, 0x90,0x23, 0,204, 0x91,0x4A, 0x80, 0x90,0x4E, 0,204, 
0x92,0x23, 0x80, 0x81, 0x90,0x56, 0,204, 0x82, 0x80, 0x90,0x2F, 0x91,0x54, 0,204, 0x80, 0x81, 0x90,0x23, 0x91,0x53, 
0,204, 0x80, 0x81, 0x90,0x4A, 0x91,0x4E, 0,204, 0x92,0x2F, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0,204, 
0x90,0x23, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x23, 0x91,0x51, 0x92,0x4A, 0,204, 0x80, 0x82, 0x81, 0x90,0x4C, 
0,204, 0x91,0x24, 0x80, 0,204, 0x90,0x48, 0,204, 0x80, 0x90,0x4C, 0,204, 0x80, 0x90,0x53, 0,204, 
0x81, 0x80, 0x90,0x32, 0x91,0x47, 0,204, 0x81, 0x91,0x48, 0,204, 0x81, 0x91,0x4A, 0,204, 0x81, 0x91,0x56, 
0,204, 0x80, 0x81, 0x90,0x30, 0x91,0x54, 0,204, 0x81, 0x91,0x53, 0,204, 0x81, 0x91,0x4A, 0x92,0x4E, 0,204, 
0x80, 0x82, 0x81, 0x90,0x2F, 0x91,0x51, 0,204, 0x81, 0,204, 0x80, 0x90,0x4F, 0x91,0x28, 0,204, 0x80, 0x81, 
0x90,0x4A, 0x91,0x2B, 0x92,0x4E, 0,204, 0x82, 0x80, 0x90,0x58, 0,204, 0x81, 0x80, 0x90,0x1C, 0,204, 0x80, 
0,204, 0x90,0x47, 0x91,0x28, 0x92,0x4C, 0,153, 0x81, 0x91,0x34, 0,51, 0x80, 0x82, 0x81, 0x90,0x53, 0x91,0x36, 
0,204, 0x80, 1,152, 0x90,0x47, 0x92,0x4C, 0,204, 0x81, 0x80, 0x82, 0x90,0x32, 0x91,0x51, 0,204, 0x81, 
0x91,0x4F, 0,204, 0x81, 0x91,0x51, 0,204, 0x81, 0x91,0x47, 0x92,0x4C, 0,204, 0x80, 0x82, 0x81, 0x90,0x34, 
0x91,0x53, 0,204, 0x81, 0,204, 0x80, 0x90,0x4F, 0x91,0x2B, 0,204, 0x80, 0x90,0x4C, 0x92,0x47, 0,204, 
0x81, 0x80, 0x82, 0x90,0x26, 0x91,0x56, 0,204, 0x80, 0x81, 0,204, 0x90,0x32, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 
0x92,0x26, 0,204, 0x80, 0x81, 0x82, 0x90,0x53, 0,204, 0x91,0x32, 0x80, 0,204, 0x81, 0x90,0x26, 0,204, 
0x91,0x4A, 0x80, 0x90,0x47, 0,204, 0x92,0x32, 0x80, 0x81, 0x90,0x56, 0,204, 0x82, 0x80, 0x90,0x54, 0,204, 
0x91,0x26, 0x80, 0x90,0x53, 0,204, 0x81, 0x80, 0x90,0x26, 0x91,0x4A, 0x92,0x47, 0,204, 0x80, 0x82, 0x81, 0x90,0x32, 
0x91,0x51, 0,204, 0x80, 0x81, 0,204, 0x90,0x26, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x51, 0x91,0x47, 0x92,0x4A, 
0,204, 0x82, 0x81, 0x80, 0x90,0x56, 0,204, 0x80, 0,204, 0x90,0x2F, 0,204, 0x91,0x4A, 0x80, 0x90,0x4E, 
0x92,0x23, 0,204, 0x80, 0x81, 0x82, 0x90,0x53, 0,204, 0x91,0x2F, 0x80, 0,204, 0x81, 0x90,0x23, 0,204, 
0x91,0x51, 0x80, 0x90,0x4E, 0x92,0x4A, 0,204, 0x82, 0x81, 0x80, 0x90,0x58, 0,204, 0x80, 0,204, 0x90,0x23, 
0x91,0x53, 0,204, 0x80, 0x81, 0x90,0x1F, 0x91,0x47, 0x92,0x4A, 0,204, 0x80, 0x82, 0x81, 0x90,0x2F, 0x91,0x51, 
0,204, 0x80, 0x81, 0,204, 0x90,0x23, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x2F, 0x91,0x47, 0x92,0x4A, 0,204, 
0x80, 0x82, 0x81, 0x90,0x4C, 0,204, 0x91,0x21, 0x80, 0,204, 0x90,0x47, 0,204, 0x80, 0x90,0x48, 0,204, 
0x80, 0x90,0x4E, 0,204, 0x81, 0x80, 0x90,0x2D, 0x91,0x48, 0,204, 0x80, 0x81, 0x90,0x21, 0x91,0x4C, 0,204, 
0x81, 0x91,0x4F, 0,204, 0x81, 0x91,0x4A, 0,204, 0x80, 0x81, 0x90,0x23, 0x91,0x4E, 0,204, 0x81, 0x91,0x51, 
0,204, 0x81, 0x91,0x47, 0,204, 0x80, 0x81, 0x90,0x2F, 0x91,0x53, 0,204, 0x81, 0x91,0x4A, 0,204, 0x81, 
0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x23, 0x91,0x51, 0,204, 0x81, 0x91,0x58, 0,204, 0x80, 0x81, 0x90,0x24, 
0,204, 0x80, 0,204, 0x90,0x47, 0x91,0x24, 0x92,0x4C, 0,204, 0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x30, 
0x80, 0,204, 0x81, 0x90,0x24, 0,204, 0x91,0x47, 0x80, 0x90,0x4C, 0,204, 0x92,0x24, 0x80, 0x81, 0x90,0x51, 
0,204, 0x82, 0x80, 0x90,0x30, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x24, 0x91,0x51, 0,204, 0x80, 0x81, 0x90,0x47, 
0x91,0x4C, 0,204, 0x92,0x30, 0x81, 0x80, 0x90,0x53, 0,204, 0x82, 0x80, 0,204, 0x90,0x2B, 0x91,0x4F, 0,204, 
0x80, 0x81, 0x90,0x2D, 0x91,0x4C, 0x92,0x47, 0,204, 0x80, 0x82, 0x81, 0x90,0x32, 0x91,0x56, 0,204, 0x80, 0x81, 
0,204, 0x90,0x32, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0x92,0x26, 0,204, 0x80, 0x81, 0x82, 0x90,0x53, 0,204, 
0x91,0x32, 0x80, 0,204, 0x81, 0x90,0x26, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0,204, 0x92,0x3E, 0x80, 0x81, 
0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x4F, 0,204, 0x91,0x3C, 0x80, 0x90,0x51, 0,204, 0x81, 0x80, 0x90,0x47, 
0x91,0x4A, 0,204, 0x92,0x3B, 0x81, 0x80, 0x90,0x4E, 0,204, 0x82, 0x80, 0x90,0x26, 0,204, 0x91,0x4F, 0x80, 
0x90,0x2B, 0,204, 0x81, 0x80, 0x90,0x47, 0x91,0x2D, 0x92,0x4A, 0,204, 0x81, 0x82, 0x80, 0x90,0x32, 0x91,0x56, 
0,204, 0x80, 0x81, 0x90,0x28, 0,204, 0x80, 0,204, 0x90,0x4A, 0x91,0x1C, 0x92,0x4E, 0,204, 0x81, 0x80, 
0x82, 0x90,0x53, 0,204, 0x91,0x34, 0x80, 0,204, 0x81, 0x90,0x34, 0,204, 0x91,0x4A, 0x80, 0x90,0x4E, 0,204, 
0x92,0x28, 0x80, 0x81, 0x90,0x56, 0,204, 0x82, 0x80, 0x90,0x2B, 0x91,0x54, 0,204, 0x80, 0x81, 0x90,0x28, 0x91,0x53, 
0,204, 0x80, 0x81, 0x90,0x4A, 0x91,0x4E, 0,204, 0x92,0x28, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x1C, 
0,204, 0x91,0x4F, 0x80, 0x90,0x28, 0,204, 0x81, 0x80, 0x90,0x51, 0x91,0x2B, 0x92,0x4A, 0,204, 0x81, 0x82, 
0x80, 0x90,0x4C, 0,204, 0x91,0x21, 0x80, 0,204, 0x90,0x48, 0,204, 0x80, 0x90,0x4C, 0,204, 0x80, 0x90,0x53, 
0,204, 0x81, 0x80, 0x90,0x2D, 0x91,0x47, 0,204, 0x80, 0x81, 0x90,0x21, 0x91,0x48, 0,204, 0x81, 0x91,0x4A, 
0,204, 0x81, 0x91,0x56, 0,204, 0x80, 0x81, 0x90,0x23, 0x91,0x54, 0,204, 0x81, 0x91,0x53, 0,204, 0x81, 
0x91,0x4A, 0x92,0x4E, 0,204, 0x80, 0x82, 0x81, 0x90,0x2F, 0x91,0x51, 0,204, 0x80, 0x81, 0,204, 0x90,0x23, 
0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x2F, 0x91,0x4A, 0x92,0x4E, 0,204, 0x80, 0x82, 0x81, 0x90,0x58, 0,204, 
0x91,0x24, 0x80, 0,204, 0x81, 0,204, 0x90,0x47, 0x91,0x24, 0x92,0x4C, 0,204, 0x81, 0x80, 0x82, 0x90,0x53, 
0,204, 0x91,0x30, 0x80, 0,204, 0x81, 0x90,0x24, 0,204, 0x91,0x47, 0x80, 0x90,0x4C, 0,204, 0x92,0x24, 
0x80, 0x81, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x30, 0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x30, 0x91,0x51, 0,204, 
0x80, 0x81, 0x90,0x47, 0x91,0x4C, 0,204, 0x92,0x24, 0x81, 0x80, 0x90,0x53, 0,204, 0x82, 0x80, 0,204, 0x90,0x2B, 
0x91,0x4F, 0,204, 0x80, 0x81, 0x90,0x2D, 0x91,0x4C, 0x92,0x47, 0,204, 0x80, 0x82, 0x81, 0x90,0x32, 0x91,0x56, 
0,204, 0x80, 0x81, 0,204, 0x90,0x32, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0x92,0x26, 0,204, 0x80, 0x81, 
0x82, 0x90,0x53, 0,204, 0x91,0x32, 0x80, 0,204, 0x81, 0x90,0x26, 0,204, 0x91,0x4A, 0x80, 0x90,0x47, 0,204, 
0x92,0x32, 0x80, 0x81, 0x90,0x56, 0,204, 0x82, 0x80, 0x90,0x54, 0,204, 0x91,0x30, 0x80, 0x90,0x53, 0,204, 
0x81, 0x80, 0x90,0x4A, 0x91,0x47, 0,204, 0x92,0x2B, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x2A, 0,204, 
0x91,0x4F, 0x80, 0x90,0x2B, 0,204, 0x81, 0x80, 0x90,0x51, 0x91,0x2D, 0x92,0x47, 0,204, 0x81, 0x82, 0x80, 0x90,0x32, 
0x91,0x56, 0,204, 0x80, 0x81, 0x90,0x23, 0,204, 0x80, 0,204, 0x90,0x4A, 0x91,0x23, 0x92,0x4E, 0,204, 
0x81, 0x80, 0x82, 0x90,0x53, 0,204, 0x91,0x2F, 0x80, 0,204, 0x81, 0x90,0x23, 0,204, 0x91,0x51, 0x80, 0x90,0x4E, 
0x92,0x4A, 0,204, 0x82, 0x81, 0x80, 0x90,0x58, 0,204, 0x80, 0x90,0x2F, 0,204, 0x91,0x53, 0x80, 0x90,0x23, 
0,204, 0x81, 0x80, 0x90,0x47, 0x91,0x4A, 0,204, 0x92,0x2F, 0x81, 0x80, 0x90,0x51, 0,204, 0x82, 0x80, 0x90,0x2F, 
0,204, 0x91,0x4F, 0x80, 0x90,0x23, 0,204, 0x81, 0x80, 0x90,0x47, 0x91,0x26, 0x92,0x4A, 0,204, 0x81, 0x82, 
0x80, 0x90,0x28, 0x91,0x4C, 7,40, 0x81, 0,4, 0x80, 0xf0};

// This score contains 5147 bytes, and 3 tone generators are used.
// 40 notes had to be skipped.
Attiny85Playtune tiny85;
void setup () {
    tiny85.tune_initchan(PB0,PB1,PB2);      // initialize the I/O ports
	tiny85.begin();
}
void loop(){
 tiny85.tune_playscore (score); 
      while (tiny85.tune_playing) {
  
          
       
        } 
        tiny85.tune_delay(5000);
}