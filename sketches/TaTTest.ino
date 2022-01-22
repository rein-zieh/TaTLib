/*
 * TaTTest.ino
 * 
 * Test Scratch for the TaT-Toolkit
 *
 * This and That Toolkit (TaT) - V 0.1
 * A Collection of various Arduino programs and elctronic circuits for model railways
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2021 Frank Reins (github@rein-zieh.de)
 *
 * This program comes with ABSOLUTELY NO WARRANTY
 */

// #define DEBUG 1
 
#include <TaTLed.h>
#include <TaTButtons.h>

TaTLed led1(13);
TaTLed led2(14);
TaTButtonOnOff button(2);

void setup() {
  // put your setup code here, to run once:

  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Start");
  #endif
  
  delay(10); // for safety

  led1.setRandomDelay(2000,2000);
  led2.setRandomDelay(0,2000,0,2000);
  
  button.connect(&led1);
  button.connect(&led2);
}

void loop() {
  // put your main code here, to run repeatedly:

  button.tick();
  led1.tick();
  led2.tick();
}
