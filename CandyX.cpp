#include "Arduino.h"
#include "CandyX.h"
#include <RotaryEncoder.h>
#include <MIDI.h>
#include "CandyX.h"

MIDI_CREATE_DEFAULT_INSTANCE();

RotaryEncoder encoder(18, 19);
RotaryEncoder encoder1(2, 3);
CandyX CandyX;


void refreshShift(byte channel, byte control_n, byte value) {
  int n_led = 0;

  if (channel == MIDI_VUMETERS_CHANNEL) {
    if (control_n == 0) {
      n_led = (value >> BITSHIFT);
      for (int i = 0; i < n_led; i++) {
        CandyX.digitalWriteCX(i, HIGH);
      }
      for (int i = 0; i < (16 - n_led); i++) {   //Calcula con (16 - n_led) el numero de led que tiene que apagar
        CandyX.digitalWriteCX((i + (16 - n_led)), LOW); //IO2, pin 2 //i + n_led hace de "offset" para que el for empiece a apagar a partir del ultimo led encendido
      }
    }
    
    n_led = 0;
    if (control_n == 1){
      n_led = (value >> BITSHIFT);
      for (int i = 0; i < n_led; i++) {
        CandyX.digitalWriteCX((i + NLEDS_PER_VUMETER), HIGH);
      }
      for (int i = 0; i < (16 - n_led); i++) {
        CandyX.digitalWriteCX(((i + NLEDS_PER_VUMETER) + (16 - n_led)), LOW);
      }
    }
    
    n_led = 0;
    if (control_n == 2){
      n_led = (value >> BITSHIFT);
      for (int i = 0; i < n_led; i++) {
        CandyX.digitalWriteCX((i + 2*NLEDS_PER_VUMETER), HIGH);
      }
      for (int i = 0; i < (16 - n_led); i++) {
        CandyX.digitalWriteCX(((i + 2*NLEDS_PER_VUMETER) + (16 - n_led)), LOW);
      }
    }
    
    n_led = 0;
    if (control_n == 3){
      n_led = (value >> BITSHIFT);
      for (int i = 0; i < n_led; i++) {
        CandyX.digitalWriteCX((i + 3*NLEDS_PER_VUMETER), HIGH);
      }
      for (int i = 0; i < (16 - n_led); i++) {
        CandyX.digitalWriteCX(((i + 3*NLEDS_PER_VUMETER) + (16 - n_led)), LOW);
      }
    }
    
    n_led = 0;
    if (control_n == 4){
      n_led = (value >> BITSHIFT);
      for (int i = 0; i < n_led; i++) {
        CandyX.digitalWriteCX((i + 4*NLEDS_PER_VUMETER), HIGH);
      }
      for (int i = 0; i < (16 - n_led); i++) {
        CandyX.digitalWriteCX(((i + 4*NLEDS_PER_VUMETER) + (16 - n_led)), LOW);
      }
    }
    
    n_led = 0;
    if (control_n == 5){
      n_led = (value >> BITSHIFT);
      for (int i = 0; i < n_led; i++) {
        CandyX.digitalWriteCX((i + 5*NLEDS_PER_VUMETER), HIGH);
      }
      for (int i = 0; i < (16 - n_led); i++) {
        CandyX.digitalWriteCX(((i + 5*NLEDS_PER_VUMETER) + (16 - n_led)), LOW);
      }
    }
    
    n_led = 0;
    if (control_n == 6){
      n_led = (value >> BITSHIFT);
      for (int i = 0; i < n_led; i++) {
        CandyX.digitalWriteCX((i + 6*NLEDS_PER_VUMETER), HIGH);
      }
      for (int i = 0; i < (16 - n_led); i++) {
        CandyX.digitalWriteCX(((i + 6*NLEDS_PER_VUMETER) + (16 - n_led)), LOW);
      }
    }
    
    n_led = 0;
    if (control_n == 7){
      n_led = (value >> BITSHIFT);
      for (int i = 0; i < n_led; i++) {
        CandyX.digitalWriteCX((i + 7*NLEDS_PER_VUMETER), HIGH);
      }
      for (int i = 0; i < (16 - n_led); i++) {
        CandyX.digitalWriteCX(((i + 7*NLEDS_PER_VUMETER) + (16 - n_led)), LOW);
      }
    }
  }
}

void setup()
{
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleControlChange(refreshShift);

}

void loop()
{
  CandyX.buttonsRead();
  CandyX.potentiometersRead();
  
  static int pos = 60;
  encoder.tick();

  int newPos = encoder.getPosition();
  if (pos != newPos) {
    if (pos < newPos) {
      MIDI.sendControlChange(15, 1, 2);
    } else if (pos > newPos) {
      MIDI.sendControlChange(15, 127, 2);
    }
    pos = newPos;
  }

  static int pos1 = 60;
  encoder1.tick();

  int newPos1 = encoder1.getPosition();
  if (pos1 != newPos1) {
    if (pos1 < newPos1) {
      MIDI.sendControlChange(16, 1, 2);
    } else if (pos1 > newPos1) {
      MIDI.sendControlChange(16, 127, 2);
    }
    pos1 = newPos1;
  }
}


CandyX::CandyX() {
  _S0 = 7;
  _S1 = 8;
  _S2 = 9;
  _S3 = 10;
  _S4 = 11;
  _OUTMD = 8;
  _IOS1 = 10;
  _IOS2 = 11;
  _IOS3 = 12;
  _IO1 = A0;
  _IO2 = A1;
  _IO3 = A2;


  pinMode(_S0, OUTPUT);
  pinMode(_S1, OUTPUT);
  pinMode(_S2, OUTPUT);
  pinMode(_S3, OUTPUT);
  pinMode(_OUTMD, OUTPUT);
  digitalWrite(_OUTMD, LOW);
  pinMode(_IOS1, OUTPUT);
  pinMode(_IOS2, OUTPUT);
  pinMode(_IOS3, OUTPUT);
}

void CandyX::initCandyX(int S0, int S1, int S2, int S3, int S4) {
  _S0 = S0;
  _S1 = S1;
  _S2 = S2;
  _S3 = S3;
  _S4 = S4;
  _OUTMD = 8;
  _IOS1 = 10;
  _IOS2 = 11;
  _IOS3 = 12;
  _IO1 = A0;
  _IO2 = A1;
  _IO3 = A2;


  pinMode(_S0, OUTPUT);
  pinMode(_S1, OUTPUT);
  pinMode(_S2, OUTPUT);
  pinMode(_S3, OUTPUT);
  pinMode(_S4, OUTPUT);
  pinMode(_OUTMD, OUTPUT);
  digitalWrite(_OUTMD, LOW);
  pinMode(_IOS1, OUTPUT);
  pinMode(_IOS2, OUTPUT);
  pinMode(_IOS3, OUTPUT);
}

void CandyX::buttonsRead() {
  for (int i = 0; i < BUTTONS_NUMBER; i++) {

    digitalWrite(_S4, bitRead(i, 4));
    digitalWrite(_S3, bitRead(i, 3));
    digitalWrite(_S2, bitRead(i, 2));
    digitalWrite(_S1, bitRead(i, 1));
    digitalWrite(_S0, bitRead(i, 0));

    _shiftReg1[i] = !digitalRead(BUTTONS_MUX_PIN);

    if (_shiftReg1[i] != _last_shiftReg1[i]) {
      //Serial.println(_shiftReg1[i]);

      if(_shiftReg1[i] == HIGH){
        MIDI.sendNoteOn(i, 127, MIDI_BUTTONS_CHANNEL);
      }
      if(_shiftReg1[i] == LOW){
        MIDI.sendNoteOff(i, 0, MIDI_BUTTONS_CHANNEL);
      }
    }
    _last_shiftReg1[i] = _shiftReg1[i];
  }
}

int CandyX::potentiometersRead() {
  for (int i = 0; i < POTS_NUMBER; i++) {

    digitalWrite(_S4, bitRead(i, 4));
    digitalWrite(_S3, bitRead(i, 3));
    digitalWrite(_S2, bitRead(i, 2));
    digitalWrite(_S1, bitRead(i, 1));
    digitalWrite(_S0, bitRead(i, 0));

    _shiftReg3[i] = analogRead(POTS_MUX_PIN);

    if (_shiftReg3[i] >> 3 != _last_shiftReg3[i] >> 3 ) {
     // Serial.println(_shiftReg3[i] >> 3);
     MIDI.sendControlChange(i, _shiftReg3[i] >> 3, MIDI_POTENTIOMETERS_CHANNEL);
    }
    _last_shiftReg3[i] = _shiftReg3[i];
  }
}

void CandyX::digitalWriteCX(int n, bool value) {
    digitalWrite(_S4, bitRead(n, 4));
    digitalWrite(_S3, bitRead(n, 3));
    digitalWrite(_S2, bitRead(n, 2));
    digitalWrite(_S1, bitRead(n, 1));
    digitalWrite(_S0, bitRead(n, 0));

    digitalWrite(LEDS_MUX_PIN, value);

}
