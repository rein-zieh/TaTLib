/*
 * Lokschuppen_1.ino
 * 
 * Scratch für eine Lokschuppenbeleuchtung
 * - 3 Neonröhren in der Halle (kalt-weiße LEDs)
 * - 1 Leuchte am Einfahrtstor (warm-weiße LED)
 * - 1 Schweißer im Lokschuppen (blau-weiße LED)
 * - 3 Buttons zum Ein-/Ausschalten
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

#include <TaTPattern.h>
#include <TaTTube.h>
#include <TaTWelder.h>
#include <TaTButtons.h>

TaTTube tube1(13);
TaTTube tube2(14);
TaTTube tube3(15);
TaTLed led(16);
TaTWelder welder(17);
TaTButtonOnOff button1(2);
TaTButtonOnOff button2(3);
TaTButtonOnOff button3(4);

void setup() {
  // put your setup code here, to run once:
  delay(10); // for safety

  tube1.setStartDelay(500,1000);
  tube2.setStartDelay(1000,1000);
  tube3.setStartDelay(1500,1000);

  tube1.setEndDelay(100);
  tube2.setEndDelay(300);
  tube3.setEndDelay(500);

  tube1.setStartPattern(TaTPatternDigitalTube, 30, 25);
  tube2.setStartPattern(TaTPatternDigitalTube, 20, 20);
  tube3.setStartPattern(TaTPatternDigitalTube, 25, 25);

  tube1.setRestartPattern(TaTPatternDigitalTube, 30, 15);
  tube2.setRestartPattern(TaTPatternDigitalTube, 20, 15);
  tube3.setRestartPattern(TaTPatternDigitalTube, 25, 15);

  int x = random(3);
  if (x == 0) tube1.setFailure(10000,10000,1000);
  if (x == 1) tube2.setFailure(10000,10000,1000);
  if (x == 2) tube3.setFailure(10000,10000,1000);

  welder.setStartDelay(1000,1000);
  welder.setPause(100, 1000); 
  welder.addPattern(TaTPatternDigitalWelder_1, 30, 20);
  welder.addPattern(TaTPatternDigitalWelder_2, 20, 15);
  welder.addPattern(TaTPatternDigitalWelder_2, 30, 10);

  button1.connect(&tube1);
  button1.connect(&tube2);
  button1.connect(&tube3);
  button2.connect(&led);
  button3.connect(&welder);
}

void loop() {
  // put your main code here, to run repeatedly:
  button1.tick();
  button2.tick();
  button3.tick();
  tube1.tick();
  tube2.tick();
  tube3.tick();
  led.tick();
  welder.tick();
}
