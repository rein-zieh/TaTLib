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

void TaTLed::setDelay(uint32_t start, uint32_t end) {
    startDelay = start;
    endDelay = end;
}

void TaTLed::setRandomDelay(uint32_t startmax, uint32_t endmax) {
    randomStartDelayMin = 0;
    randomStartDelayMax = startmax;
    randomEndDelayMin = 0;
    randomEndDelayMax = endmax;
}
void TaTLed::setRandomDelay(uint32_t startmin, uint32_t startmax, uint32_t endmin, uint32_t endmax) {
    randomStartDelayMin = startmin;
    randomStartDelayMax = startmax;
    randomEndDelayMin = endmin;
    randomEndDelayMax = endmax;
}

void TaTLed::on() {
    statusShould = TAT_START;
    startDelay = randomStartDelayMax ? random(randomStartDelayMin, randomStartDelayMax) : startDelay;
}

void TaTLed::off() {
    statusShould = TAT_END;
    endDelay = randomEndDelayMax ? random(randomEndDelayMin, randomEndDelayMax) : endDelay;
}

void TaTLed::tick() {
    // Status change
    if (statusShould != statusIs) {

        #ifdef DEBUG
            Serial.println(statusShould);
        #endif

        statusIs = statusShould;
        switch (statusIs) {
            case TAT_OFF : {
                #ifdef DEBUG
                    Serial.print("PIN aus: ");
                    Serial.println(pin);
                #endif

                if (pin) digitalWrite(pin, LOW);
                return;
            }
            case TAT_ON : {
                #ifdef DEBUG
                    Serial.print("PIN ein: ");
                    Serial.println(pin);
                #endif

                if (pin) digitalWrite(pin, HIGH);
                return;
            }
            case TAT_START : {
                timer.set(startDelay);
                return;
            }
            case TAT_END : {
                timer.set(endDelay);
                return;
            }
        }
    }
    // End of start delay
    if (statusIs == TAT_START && timer.check()) {
        statusShould = TAT_ON;
    }
    // End of end delay
    if (statusIs == TAT_END && timer.check()) {
        statusShould = TAT_OFF;
    }
}
