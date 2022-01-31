/*
 * TaTWelder.cpp
 * 
 * Class for a welding machine
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

#include "TaTWelder.h"

TaTWelder::TaTWelder():TaTLed() {}
TaTWelder::TaTWelder(uint8_t pin):TaTLed(pin) {}

void TaTWelder::addPattern(uint8_t *pattern, uint32_t patternSize, uint32_t patternFrequence, bool pwm) {
    if (nrPattern < TAT_MAX_PATTERN_FOR_WELDER) {
        this->pattern[nrPattern] = pattern;
        this->patternSize[nrPattern] = patternSize;
        this->patternFrequence[nrPattern] = patternFrequence;
        this->patternPwm[nrPattern] = pwm;

        nrPattern++;
    }
}

void TaTWelder::setPause(uint32_t pause, uint32_t variation) {
    this->pause = pause;
    this->pauseVariation = variation;
}

void TaTWelder::on() {
    statusShould = WELDER_START;
    startDelay += random(startVariation);
}

void TaTWelder::off() {
    statusShould = WELDER_END;
    endDelay += random(endVariation);
}

void TaTWelder::tick() {

    /*
     * Status should change
     */
    if (statusShould != statusIs) {
        #ifdef DEBUG
            Serial.print("status changed: ");
            Serial.println(statusShould);
        #endif
        statusIs = statusShould;
        switch (statusIs) {
            case WELDER_OFF : {
                if (pin) digitalWrite(pin, LOW);
                return;
            }
            case WELDER_PAUSE : {
                if (pin) digitalWrite(pin, LOW);
                timer.set(pause + random(pauseVariation));
                return;
            }
            case WELDER_PATTERN_EVEN : {
                uint8_t value = pattern[actualPattern][patternIndex];
                if (pin) {
                    if (patternPwm[actualPattern])
                        analogWrite(pin, value);
                    else 
                        digitalWrite(pin, value);
                }
                timer.set(patternFrequence[actualPattern]);
                return;
            }
            case WELDER_PATTERN_ODD : {
                uint8_t value = pattern[actualPattern][patternIndex];
                if (pin) {
                    if (patternPwm[actualPattern])
                        analogWrite(pin, value);
                    else 
                        digitalWrite(pin, value);
                }
                timer.set(patternFrequence[actualPattern]);
                return;
            }
            case WELDER_START : {
                timer.set(startDelay);
                return;
            }
            case WELDER_END : {
                timer.set(endDelay);
                return;
            }
        }
    }

    /*
     * Check Timer and set to next steps
     */
    if (timer.check()) {
        switch (statusIs) {
            case WELDER_START : {
                // End of start delay
                if (nrPattern) {
                    actualPattern = random(nrPattern);
                    patternIndex = 0;
                    statusShould = WELDER_PATTERN_EVEN;
                }
                break;
            }
            case WELDER_END : {
                // End of end delay
                statusShould = WELDER_OFF;
                break;
            }
            case WELDER_PAUSE : {
                // End of pause
                if (nrPattern) {
                    actualPattern = random(nrPattern);
                    patternIndex = 0;
                    statusShould = WELDER_PATTERN_EVEN;
                }
                break;
            }
            /* 
            * Um das Programmiermuster konsistent zu halten wurden, für die Pattern 2 Status verwendet,
            * da der obere Teil dieser Funktion nur auf Statusänderungen reagiert
            */
            case WELDER_PATTERN_EVEN : {
                // End of Pattern with even index
                patternIndex++;
                if (patternIndex >= patternSize[actualPattern]) {
                    statusShould = WELDER_PAUSE;
                } else {
                    statusShould = WELDER_PATTERN_ODD;
                }
                break;
            }
            case WELDER_PATTERN_ODD : {
                // End of Pattern with odd index
                patternIndex++;
                if (patternIndex >= patternSize[actualPattern]) {
                    statusShould = WELDER_PAUSE;
                } else {
                    statusShould = WELDER_PATTERN_EVEN;
                }
                break;
            }
        }
    }
}

