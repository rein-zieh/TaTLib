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
 
#include <TaTPattern.h>
#include <TaTTube.h>
#include <TaTWelder.h>
#include <TaTButtons.h>

//TaTTube tube(13);
TaTWelder welder(13);
TaTButtonOnOff button(2);

void setup() {
  // put your setup code here, to run once:

  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Start");
  #endif
  
  delay(10); // for safety

  //tube.setStartDelay(1000,3000);
  //tube.setEndDelay(1000,3000);
  //tube.setFailure(2000,3000,1000);
  //tube.setStartPattern(TaTPatternDigitalTube, 30, 40);
  //tube.setRestartPattern(TaTPatternDigitalTube, 30, 20);
 
  welder.setStartDelay(1000,1000);
  welder.setPause(100, 1000); 
  welder.addPattern(TaTPatternDigitalWelder_1, 30, 20);
  welder.addPattern(TaTPatternDigitalWelder_2, 20, 15);
  welder.addPattern(TaTPatternDigitalWelder_2, 30, 10);

  //button.connect(&welder);

  welder.on();
}

void loop() {
  // put your main code here, to run repeatedly:

  button.tick();
  //tube.tick();
  welder.tick();
}
