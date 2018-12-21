/**************************************************************************
* 
* Playtune: An Arduino Tune Generator
* 
* Plays a polyphonic musical score
* For documentation, see the Playtune.cpp source code file
* 
*   (C) Copyright 2011,2016 Len Shustek
*    Modified by David Rubio September 2018 
*
**************************************************************************/
/*
* Change log
*  19 January 2011, L.Shustek, V1.0: Initial release.
*  10 June 2013, L. Shustek, V1.3
*     - change for compatibility with Arduino IDE version 1.0.5
*   6 April 2015, L. Shustek, V1.4
*     - change for compatibility with Arduino IDE version 1.6.x
*  28 May 2016, T. Wasiluk
*     - added support for ATmega32U4
*  10 July 2016, Nick Shvelidze
*     - Fixed include file names for Arduino 1.6 on Linux.
*  08/09/18, David Rubio
*     added support for the popular attiny85 based on L.Shustek attiny4313 menorah November 25, 2013 
*/

#ifndef Attiny85_Playtune_h
#define Attiny85_Playtune_h

#include <Arduino.h>

class Attiny85Playtune
{
public:
 void tune_initchan (byte pin,byte pin1,byte pin2);			// assign a timer to an output pin
 void tune_playscore (const byte *score);	// start playing a polyphonic score
 volatile static bool tune_playing;	// is the score still playing?
 void tune_stopscore (void);			// stop playing the score
 void begin (void);			// starts timers
 void tune_delay (unsigned msec);		// delay in milliseconds
 void tune_stopchans (void);			// stop all timers
};

#endif
