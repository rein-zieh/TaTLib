/*
 * TaTLed.cpp
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

// #define DEBUG 1

#include "TaTLed.h"

TaTLed::TaTLed():TaTActor() {}
TaTLed::TaTLed(uint8_t pin):TaTActor(pin) {
    if (pin) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
}

void TaTLed::init(uint8_t pin) {
    TaTActor::init(pin);
    if (pin) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
}

void TaTLed::setStartDelay(uint32_t start, uint32_t variation = 0) {
    startDelay = start;
    startVariation = variation;
}
void TaTLed::setEndDelay(uint32_t end, uint32_t variation = 0) {
    endDelay = end;
    endVariation = variation;
}

void TaTLed::on() {
    statusShould = LED_START;
    startDelay += random(startVariation);
}

void TaTLed::off() {
    statusShould = LED_END;
    endDelay += random(endVariation);
}

void TaTLed::tick() {
    // Status change
    if (statusShould != statusIs) {

        #ifdef DEBUG
            Serial.println(statusShould);
        #endif

        statusIs = statusShould;
        switch (statusIs) {
            case LED_OFF : {
                #ifdef DEBUG
                    Serial.print("PIN aus: ");
                    Serial.println(pin);
                #endif

                if (pin) digitalWrite(pin, LOW);
                return;
            }
            case LED_ON : {
                #ifdef DEBUG
                    Serial.print("PIN ein: ");
                    Serial.println(pin);
                #endif

                if (pin) digitalWrite(pin, HIGH);
                return;
            }
            case LED_START : {
                timer.set(startDelay);
                return;
            }
            case LED_END : {
                timer.set(endDelay);
                return;
            }
        }
    }
    if (timer.check()) {
        switch (statusIs) {
            case LED_START : {
                statusShould = LED_ON;
                break;
            }
            case LED_END : {
                statusShould = LED_OFF;
                break;
            }
        }
    }
}
