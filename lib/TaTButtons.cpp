/*
 * TaTPushButton.cpp
 * 
 * Class for a LED
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

#include "TaTButtons.h"

TaTButton::TaTButton()
: TaTSensor() {
}

TaTButton::TaTButton(uint8_t pin, uint32_t tremor)
: TaTSensor() {
  init(pin, tremor);
}

void TaTButton::init(uint8_t pin, uint32_t tremor) {
    TaTSensor::init(pin);
    if (pin) {
        pinMode(pin, INPUT);
    }
    setTremor(tremor);
}

void TaTButton::setTremor(uint32_t tremor) {
  this->tremor = tremor;
}

void TaTButton::tick() {
  int read = digitalRead(pin);

   // Button Änderung:
  if (read != prevRead) {
    prevRead = read;  // Status sichern für nächsten Tick
    lastTime = millis();    // Zeit der letzten Änderung merken
  }

  //Wenn es kein "Rauschen" ist
  if ((millis() - lastTime) > tremor) {
   
    if (read && !sensorState)  {
      on();
    } else if (!read && sensorState) {
      off();
    }
  
  }
}

// =================================================

TaTButtonInv::TaTButtonInv()
: TaTButton() {
}

TaTButtonInv::TaTButtonInv(uint8_t pin, uint32_t tremor)
: TaTButton(pin, tremor) {
}

void TaTButtonInv::tick() {
  int read = digitalRead(pin);

   // Button Änderung:
  if (read != prevRead) {
    prevRead = read;  // Status sichern für nächsten Tick
    lastTime = millis();    // Zeit der letzten Änderung merken
  }

  //Wenn es kein "Rauschen" ist
  if ((millis() - lastTime) > tremor) {

    if (read && sensorState)  {
      off();
    } else if (!read && !sensorState) {
      on();
    }

  }
}

// =================================================

TaTButtonOnOff::TaTButtonOnOff()
: TaTButton() {
}

TaTButtonOnOff::TaTButtonOnOff(uint8_t pin, uint32_t tremor)
: TaTButton(pin, tremor) {
}

void TaTButtonOnOff::tick() {
  uint8_t read = digitalRead(pin);

  // Button Änderung:
  if (read != prevRead) {
    prevRead = read;  // Status sichern für nächsten Tick
    lastTime = millis();    // Zeit der letzten Änderung merken
  }

  //Wenn es kein "Rauschen" ist
  if ((millis() - lastTime) > tremor) {

    // Buttonstatus hat sich verändert:
    if (read != buttonState) {
      buttonState = read;

      //Wenn Button gedrückt wurde (von LOW nach HIGH)
      if (buttonState) {
        sensorState = !sensorState; //Toggle den Status
        
        if (sensorState) {
            on();
        } else {
            off();
        }
      }
    }

  }
}