#include "Arduino.h"

#ifndef CandyX_h
#define CandyX_h

//-----------------------SET YOUR DESIRED SETTINGS HERE---------------------------------------------------------------------------------------//

#define POTS_NUMBER  1          //Number of the potentiometers that you want(MAX:32)
#define LEDS_NUMBER  32         //Number of LEDs that you want (preferably 4, 8, 16 or 32)(MAX:32)
#define BUTTONS_NUMBER  3       //Number of buttons that you want (MAX:32)

#define MIDI_VUMETERS_CHANNEL 1            //MIDI channel number of the Vumeters data
#define MIDI_POTENTIOMETERS_CHANNEL 2      //MIDI channel number of the potentiometers data
#define MIDI_BUTTONS_CHANNEL 3             //MIDI channel number of the buttons data

#define NLEDS_PER_VUMETER 32      //Number of LEDs you want for each vumeter(It can only be 4, 8, 16 or 32

#define POTS_MUX_PIN 4
#define LEDS_MUX_PIN 5
#define BUTTONS_MUX_PIN 6

//--------------------------------------------------------------------------------------------------------------------------------------------//





//----------------------- IMPORTANT DON'T CHANGE THIS ----------------------------------------------------------------------------------------//

#if defined NLEDS_PER_VUMETER  &&  NLEDS_PER_VUMETER == 32
#define BITSHIFT 2
#elif defined NLEDS_PER_VUMETER  &&  NLEDS_PER_VUMETER == 16
#define BITSHIFT 3
#elif defined NLEDS_PER_VUMETER  &&  NLEDS_PER_VUMETER == 8
#define BITSHIFT 4
#elif defined NLEDS_PER_VUMETER  &&  NLEDS_PER_VUMETER == 4
#define BITSHIFT 5
#else
#error "NLEDS_PER_VUMETER can only be 4, 8, 16 or 32"
#endif


#if defined NLEDS_PER_VUMETER && NLEDS_PER_VUMETER > LEDS_NUMBER
#error "NLEDS_PER_VUMETER can't be higher than LEDS_NUMBER"
#endif


#if defined LEDS_NUMBER && LEDS_NUMBER > 32
#error "LEDS_NUMBER can only be up to 32"
#endif

#if defined POTS_NUMBER && POTS_NUMBER > 32
#error "POTS_NUMBER can only be up to 32"
#endif

#if defined BUTTONS_NUMBER && BUTTONS_NUMBER > 32
#error "BUTTONS_NUMBER can only be up to 32"
#endif

#define N_VUMETERS LEDS_NUMBER/NLEDS_PER_VUMETER

#define DIGITAL_IN   0
#define DIGITAL_OUT  1
#define ANALOG_IN    2
#define DIGITAL_IN_PULLUP    3

class CandyX
{
  public:
    CandyX();
    void initCandyX(int S0, int S1, int S2, int S3, int S4);
    void digitalWriteCX(int n, bool value);
    int potentiometersRead(void);
    void buttonsRead(void);
    uint8_t mapRelativeCC(int8_t value);
    uint8_t twosComplementTo7bitSignedMagnitude(int8_t value);
    int _shiftReg1[BUTTONS_NUMBER] = {0}; //Array to store the BUTTONS Input States
    int _last_shiftReg1[BUTTONS_NUMBER] = {0};
    int _shiftReg2[16] = {0};
    int _shiftReg3[POTS_NUMBER] = {0}; //Array to store the POTENTIOMETERS Input values
    int _last_shiftReg3[POTS_NUMBER] = {0};

  private:
    int _S0, _S1, _S2, _S3, _S4, _OUTMD, _IOS1, _IOS2, _IOS3, _IO1, _IO2, _IO3;
    int _LE1, _LE2, _LE3, _M1, _M2, _M3;
};

//--------------------------------------------------------------------------------------------------------------------------------------------//

#endif
