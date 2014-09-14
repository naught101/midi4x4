//LED TEST w/ 74HC595
//by Amanda Ghassaei 2012
//http://www.instructables.com/id/Multiplexing-with-Arduino-and-the-74HC595/

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

//this code will light up each led in the 4x4 matrix one at a time


//pin connections- the #define tag will replace all instances of "latchPin" in your code with A1 (and so on)
#define latchPin A1
#define clockPin A0
#define dataPin A2

//looping variables
byte i;
byte j;

//storage variable
byte dataToSendH;
byte dataToSendL;

void setup() {
    //set pins as output
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

}

void loop() {

    for (i = 0; i < 4; i++) {

        for (j = 0; j < 4; j++) {

            //dataToSend = (1 << (i+4)) | (15 & ~(1 << j));

            // i is cathode select.

            dataToSendH = ( (0xF0 & ~(1 << (i + 4))) | (0x0F & (1 << j)) ); // MSB Cathode -> Red LSB
            dataToSendL = ( (0xF0 & (1 << ((j + 1) % 4))) | (0x0F & (1 << ((j + 2) % 4))) ); // MSB Green -> Blue LSB


            //dataToSendH = 0x0f; // MSB Cathode -> Red LSB
            //dataToSendL = 0xff ; // MSB Green -> Blue LSB


            digitalWrite(latchPin, LOW);

            // shift out the bits of dataToSend to the 74HC595
            shiftOut(dataPin, clockPin, LSBFIRST, dataToSendH);
            shiftOut(dataPin, clockPin, MSBFIRST, dataToSendL);


            //set latch pin high- this sends data to outputs so the LEDs will light up
            digitalWrite(latchPin, HIGH);

            delay(200);//wait
        }
    }

}

