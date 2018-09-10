# Attiny85_Playtune_master
playtune library modified for the attiny85
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
