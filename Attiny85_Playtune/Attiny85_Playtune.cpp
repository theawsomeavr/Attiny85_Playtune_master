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
 #include "Attiny85_Playtune.h"
#define NUM_CHANS 3 // number of speaker outputs

//#define CPU_MHZ F_CPU/1000000   // ATtiny CKSEL 0100: 8 Mhz, 1x prescale (lfuse=E4)
int SPEAKER0;  // output, speaker 1 (also USB-TTL RX)
int SPEAKER1; // output, speaker 2 (also USB-TTL TX)
int SPEAKER2;
 int squarewavespins[3];
void Attiny85Playtune::tune_initchan(byte pin,byte pin1,byte pin2) {
	SPEAKER0=pin; SPEAKER1=pin1; SPEAKER2=pin2;
	squarewavespins[0]=pin;
	squarewavespins[1]=pin1;
	squarewavespins[2]=pin2;
	DDRB = (1<<SPEAKER0)+(1<<SPEAKER1)+(1<<SPEAKER2);

}





//#define PORT(x) _SFR_IO8(x)


// speaker registers
// We use constants for speaker ports because we don't want any overhead
// in the interrupt routines; the loop through the speakers there is unrolled.

#define SPEAKER0_REG PORTB  //  data register
#define SPEAKER0_DIR DDRB //  direction register

#define SPEAKER1_REG PORTB  //  data register
#define SPEAKER1_DIR DDRB //  direction register

#define SPEAKER2_REG PORTB  //  data register
#define SPEAKER2_DIR DDRB //  direction register

  //  direction register



// variable for timing

volatile unsigned int scorewait_interrupt_count;
volatile unsigned int delaywait_interrupt_count;

// variables for music-playing

volatile const byte *score_start;
volatile const byte *score_cursor;
volatile bool Attiny85Playtune::tune_playing;

volatile long accumulator [NUM_CHANS];
volatile long decrement [NUM_CHANS];
volatile bool playing [NUM_CHANS];

/* Table of accumulator decrement values, generated by a companion Excel spreadsheet.
   These depend on the polling frequency and the accumulator restart value.
   We basically do incremental division for each channel in the polling interrupt routine:
        accum -= decrement
        if (accum < 0) {
            toggle speaker output
            accum += ACCUM_RESTART
        }
*/

#define POLLTIME_USEC 50    // polling interval in microseconds
#define ACCUM_RESTART 4194304L  // 2^22 allows 1-byte addition on 3- or 4-byte numbers
#define MAX_NOTE 123

const long decrement_PGM[MAX_NOTE+1] PROGMEM = {
    3429L, 3633L, 3849L, 4078L, 4320L, 4577L, 4850L, 5138L, 5443L, 5767L, 6110L, 6473L, 
    6858L, 7266L, 7698L, 8156L, 8641L, 9155L, 9699L, 10276L, 10887L, 11534L, 12220L, 
    12947L, 13717L, 14532L, 15396L, 16312L, 17282L, 18310L, 19398L, 20552L, 21774L, 
    23069L, 24440L, 25894L, 27433L, 29065L, 30793L, 32624L, 34564L, 36619L, 38797L, 
    41104L, 43548L, 46137L, 48881L, 51787L, 54867L, 58129L, 61586L, 65248L, 69128L, 
    73238L, 77593L, 82207L, 87096L, 92275L, 97762L, 103575L, 109734L, 116259L, 123172L, 
    130496L, 138256L, 146477L, 155187L, 164415L, 174191L, 184549L, 195523L, 207150L, 
    219467L, 232518L, 246344L, 260992L, 276512L, 292954L, 310374L, 328830L, 348383L, 
    369099L, 391047L, 414299L, 438935L, 465035L, 492688L, 521984L, 553023L, 585908L, 
    620748L, 657659L, 696766L, 738198L, 782093L, 828599L, 877870L, 930071L, 985375L, 
    1043969L, 1106047L, 1171815L, 1241495L, 1315318L, 1393531L, 1476395L, 1564186L, 
    1657197L, 1755739L, 1860141L, 1970751L, 2087938L, 2212093L, 2343631L, 2482991L, 
    2630637L, 2787063L, 2952790L, 3128372L, 3314395L, 3511479L, 3720282L, 3941502L, 
    4175876L
};

void tune_playnote (byte chan, byte note);
void tune_stopnote (byte chan);
void tune_stepscore (void);


//--------------------------------------------------------------------------
// Initialize the timers
//--------------------------------------------------------------------------

void Attiny85Playtune::begin () {
    
    // We use the 8 bit timer to generate the polling interrupt for notes.
    // It should interrupt often, like every 50 microseconds.
    
    TCCR0A = (1 << WGM01);  // mode 010: CTC   
#if F_CPU==16000000
    TCCR0B = 1 << CS00; 
    TCCR0B = 1 << CS01; // clock select 011: clk/16 prescaling
    OCR0A = F_CPU/8000000 * POLLTIME_USEC;
#elif F_CPU==8000000
    TCCR0B = 1 << CS01;   // clock select 010: clk/8 prescaling
    OCR0A = F_CPU/8000000 * POLLTIME_USEC;
#else
 unusual frequency
#endif
    
    // We use the 16 bit timer both for timing scores from the interrupt routine
    // and doing mainline code waits. It interrupts once a millisecond.
    
      TCCR1 |= (1 << CTC1);  // clear timer on compare match
     //TCCR1 |= (1 << CS11);
    TCCR1 = (1 << CS12) | (1 << CS10) | (1 << CS11);  // clear timer on compare match
   // TCCR1 |= (1 << CS10);
    OCR1C = F_CPU/ 1000;

    Attiny85Playtune::tune_playing = false;    
    scorewait_interrupt_count = 0;
    delaywait_interrupt_count = 0;
    
    TIMSK =(1<<OCIE0A) | (1<<OCIE1A); // turn on match A interrupts for both timers
    interrupts();    // enable interrupts

}


//--------------------------------------------------------------------------
// Start playing a note on a particular channel
//--------------------------------------------------------------------------

void tune_playnote (byte chan, byte note) {

    //if (chan < NUM_CHANS) {
        if (note>MAX_NOTE) note=MAX_NOTE;
        decrement[chan] = pgm_read_dword(decrement_PGM + note);
        accumulator[chan] = ACCUM_RESTART;
        playing[chan]=true;
  //  }
}


//--------------------------------------------------------------------------
// Stop playing a note on a particular channel
//--------------------------------------------------------------------------

void tune_stopnote (byte chan) {
    playing[chan]= false;
	
	PORTB = (0<<squarewavespins[chan]);
}


//--------------------------------------------------------------------------
//   Play a score
//--------------------------------------------------------------------------



void Attiny85Playtune::tune_playscore (const byte *score) {
    if (Attiny85Playtune::tune_playing) tune_stopscore();
    score_start = score;
    score_cursor = score;
    tune_stepscore(); /* execute initial commands */
    Attiny85Playtune::tune_playing = true;  /* release the interrupt routine */
}

/* Do score commands until a "wait" is found, or the score is stopped.
 This is called initially from tune_playcore, but then is called
 from the interrupt routine when waits expire.
 */

//#define CMD_PLAYNOTE  0x90  /* play a note: low nibble is generator #, note is next byte */
//#define CMD_STOPNOTE  0x80  /* stop a note: low nibble is generator # */
//#define CMD_RESTART   0xe0  /* restart the score from the beginning */
//#define CMD_STOP    0xf0  /* stop playing */
/* if CMD < 0x80, then the other 7 bits and the next byte are a 15-bit big-endian number of msec to wait */

void tune_stepscore (void) {
  byte cmd, opcode, chan;

  while (1) {
    cmd = pgm_read_byte(score_cursor++);
	
    if (cmd < 0x80) {
      /* wait count is in msec. */
	
      scorewait_interrupt_count = ((unsigned)cmd << 8) | (pgm_read_byte(score_cursor++)+1);
      break;
    }
    opcode = cmd & 0xf0;
    chan = cmd & 0x0f;
    if (opcode == 0x80) {
      /* stop note */
      tune_stopnote (chan);
    }
    else if (opcode == 0x90) {
      /* play note */
      tune_playnote (chan, pgm_read_byte(score_cursor++));
    }
    else if (opcode == 0xe0) {
      /* restart score */
      score_cursor = score_start;
    }
    else if (opcode == 0xf0) {
      /* stop score */
      Attiny85Playtune::tune_playing = false;
	  tune_stopnote(0);
	  tune_stopnote(1);
	  tune_stopnote(2);
      break;
    }
  }
}

//--------------------------------------------------------------------------
// Stop playing a score
//--------------------------------------------------------------------------

void Attiny85Playtune::tune_stopscore (void) {
  tune_stopnote(0);
  tune_stopnote(1);
  tune_stopnote(2);
  // depends on NUM_CHANS==4
  Attiny85Playtune::tune_playing = false;
}

//--------------------------------------------------------------------------
// Delay a specified number of milliseconds, up to about 30 seconds.
//--------------------------------------------------------------------------

void Attiny85Playtune::tune_delay (unsigned duration) {
    boolean notdone;
    
    delaywait_interrupt_count = duration;
    do {
        // wait until the interrupt routines decrements the toggle count to zero
        noInterrupts();
        notdone = delaywait_interrupt_count != 0;  /* interrupt-safe test */
        interrupts();
    }  while (notdone);
}

//--------------------------------------------------------------------------
// Stop all channels
//--------------------------------------------------------------------------

void Attiny85Playtune::tune_stopchans(void) {

  TIMSK &= ~(1 << OCIE0A);  // disable all timer interrupts
  TIMSK &= ~(1 << OCIE1A);
}

//--------------------------------------------------------------------------
//  Timer interrupt Service Routines
//--------------------------------------------------------------------------

ISR(TIMER0_COMPA_vect) { //******* 8-bit timer: 50 microsecond interrupts
    
// We unroll code with a macro to avoid loop overhead.
// For even greater efficiency, we could write this in assembly code
// and do 3-byte instead of 4-byte arithmetic.

  #define dospeaker(spkr) if (playing[spkr]) {   \
      accumulator[spkr] -= decrement[spkr];    \
  if (accumulator[spkr]<0) {           \
      SPEAKER##spkr##_REG ^= (1<<SPEAKER##spkr); \
      accumulator[spkr] += ACCUM_RESTART;    \
    }                      \
  } 
  
  dospeaker(0);
  dospeaker(1);
  dospeaker(2);
   // Depends on NUM_CHANS==4
}
ISR(TIMER1_COMPA_vect) { //******* 16-bit timer: millisecond interrupts

    // decrement score wait counter
    if (Attiny85Playtune::tune_playing && scorewait_interrupt_count && --scorewait_interrupt_count == 0) {
        // end of a score wait, so execute more score commands
        tune_stepscore ();  // execute commands
    }
    
    // decrement delay wait counter
    if (delaywait_interrupt_count)
    --delaywait_interrupt_count; 
    // countdown for tune_delay()
    
}
