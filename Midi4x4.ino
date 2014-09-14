// LED TEST w/ 74HC595
// by Amanda Ghassaei 2012
// http:// www.instructables.com/id/Multiplexing-with-Arduino-and-the-74HC595/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

// this code will light up each led in the 4x4 matrix one at a time


// pin connections- the #define tag will replace all instances of "latchPin" in your code with A1 (and so on)
#define latchPin A1
#define clockPin A0
#define dataPin A2

// looping indexes
int ir; // row
int ic; // column
int ik; // colour
int ii; // iteration for colour bit depth/fake PWM

// colour variables
int cr;
int cg;
int cb;

// storage variable
byte dataToSendH;
byte dataToSendL;

const int colours = 3;
const int rows = 4;
const int cols = 4;
int colour_grid[][cols][rows] = {
  {
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 0, 0, 1}
  },
  {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 1, 0, 0}
  },
  {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 1, 0}
  }
};

void setup() {
  // set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

}

void loop() {

  for (ii = 0; ii < 8; ii++) {
    for (ic = 0; ic < 4; ic++) {
      for (ir = 0; ir < 4; ir++) {

        cr = colour_grid[0][ic][ir];
        cg = colour_grid[1][ic][ir] * (ii%2); // green and blue are too bright, so only light up half the time.
        cb = colour_grid[2][ic][ir] * (ii%2);


        // dataToSend = (1 << (i+4)) | (15 & ~(1 << ic));

        // ir is cathode select.

        dataToSendH = ( (0xF0 & ~(1 << (ic + 4))) | (0x0F & (cr << ir)) ); // MSB Cathode -> Red LSB
        dataToSendL = ( (0xF0 & (cg << (ir + 4))) | (0x0F & (cb << ir)) ); // MSB Green -> Blue LSB

        // dataToSendH = 0x0f; // MSB Cathode -> Red LSB
        // dataToSendL = 0xff ; // MSB Green -> Blue LSB

        digitalWrite(latchPin, LOW);

        // shift out the bits of dataToSend to the 74HC595
        shiftOut(dataPin, clockPin, LSBFIRST, dataToSendH);
        shiftOut(dataPin, clockPin, LSBFIRST, dataToSendL);

        // set latch pin high- this sends data to outputs so the LEDs will light up
        digitalWrite(latchPin, HIGH);

        delay(100);// wait
      }
    }
  }

}

