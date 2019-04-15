# CandyX-MIDI-Library
MIDI Library for Arduino based hardware

Supports Multiplexers(up to 5-bit)
         Shift Registers (Serial In-Parallel Out)
         RGB addressable LED strips (like WS2812B)
         
You can easily control up to 96 I/O with only a few settings:

        #define POTS_NUMBER  8          //Number of the potentiometers that you want(MAX:32)
        #define LEDS_NUMBER  32         //Number of LEDs that you want (preferably 4, 8, 16 or 32)(MAX:32)
        #define BUTTONS_NUMBER  7       //Number of buttons that you want (MAX:32)

        #define MIDI_VUMETERS_CHANNEL 1            //MIDI channel number of the Vumeters data
        #define MIDI_POTENTIOMETERS_CHANNEL 2      //MIDI channel number of the potentiometers data
        #define MIDI_BUTTONS_CHANNEL 3             //MIDI channel number of the buttons data

        #define NLEDS_PER_VUMETER 8     //Number of LEDs you want for each vumeter(It can only be 4, 8, 16 or 32

        #define POTS_MUX_PIN 4        //Common Pin of the MUX #1
        #define LEDS_MUX_PIN 5        //Common Pin of the MUX #2
        #define BUTTONS_MUX_PIN 6     //Common Pin of the MUX #3

As simple as that, you only has to enter those 10 values following the commented limitations and you will have your MIDI device working.

Now working with the dedicated CandyX hardware (MEGA Shield and Stand-Alone boards) available soon.

