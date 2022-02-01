/*
 * TaTTube.cpp
 * 
 * Class for a Neon Tube
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

#include "TaTTube.h"

TaTTube::TaTTube():TaTLed() {}
TaTTube::TaTTube(uint8_t pin):TaTLed(pin) {}

void TaTTube::setFailure(uint32_t interval, uint32_t variation = 0, uint32_t duration) {
    failureInterval = interval;
    failureVariation = variation;
    failureDuration = duration;
}

void TaTTube::setStartPattern(uint8_t *pattern, uint32_t patternSize, uint32_t patternFrequence = 10, bool pwm) {
    startPattern = pattern;
    startPatternSize = patternSize;
    startPatternFrequence = patternFrequence;
    startPatternPwm = pwm;
}

void TaTTube::setRestartPattern(uint8_t *pattern, uint32_t patternSize, uint32_t patternFrequence = 10, bool pwm) {
    restartPattern = pattern;
    restartPatternSize = patternSize;
    restartPatternFrequence = patternFrequence;
    restartPatternPwm = pwm;
}

void TaTTube::on() {
    statusShould = TUBE_START;
    startDelay += random(startVariation);
}

void TaTTube::off() {
    statusShould = TUBE_END;
    endDelay += random(endVariation);
}

void TaTTube::tick() {
    // Status change
    if (statusShould != statusIs) {

        #ifdef DEBUG
            Serial.print("statusShould: ");
            Serial.println(statusShould);
        #endif

        statusIs = statusShould;
        switch (statusIs) {
            case TUBE_OFF : {
                #ifdef DEBUG
                    Serial.print("PIN aus: ");
                    Serial.println(pin);
                #endif

                if (pin) digitalWrite(pin, LOW);
                return;
            }
            case TUBE_GLOW : {
                #ifdef DEBUG
                    Serial.print("PIN ein: ");
                    Serial.println(pin);
                #endif

                if (pin) digitalWrite(pin, HIGH);

                if (failureInterval) timer.set(failureInterval + random(0, failureVariation));

                return;
            }
            case TUBE_FAILURE : {
                #ifdef DEBUG
                    Serial.print("TUBE_FAILURE: ");
                    Serial.println(pin);
                #endif

                if (pin) digitalWrite(pin, LOW);
                timer.set(failureDuration);
                return;
            }
            case TUBE_RESTARTPATTERN_EVEN : {
                #ifdef DEBUG
                    Serial.print("TUBE_RESTARTPATTERN_EVEN: ");
                    Serial.println(pin);
                #endif

                uint8_t value = restartPattern[patternIndex];
                if (pin) {
                    if (restartPatternPwm)
                        analogWrite(pin, value);
                    else 
                        digitalWrite(pin, value);
                }
                timer.set(restartPatternFrequence);
                return;
            }
            case TUBE_RESTARTPATTERN_ODD : {
                #ifdef DEBUG
                    Serial.print("TUBE_RESTARTPATTERN_ODD: ");
                    Serial.println(pin);
                #endif

                uint8_t value = restartPattern[patternIndex];
                if (pin) {
                    if (restartPatternPwm)
                        analogWrite(pin, value);
                    else 
                        digitalWrite(pin, value);
                }
                timer.set(restartPatternFrequence);
                return;
            }
            case TUBE_STARTPATTERN_EVEN : {
                #ifdef DEBUG
                    Serial.print("TUBE_STARTPATTERN_EVEN: ");
                    Serial.println(pin);
                #endif

                uint8_t value = startPattern[patternIndex];
                if (pin) {
                    if (startPatternPwm)
                        analogWrite(pin, value);
                    else 
                        digitalWrite(pin, value);
                }
                timer.set(startPatternFrequence);
                return;
            }
            case TUBE_STARTPATTERN_ODD : {
                #ifdef DEBUG
                    Serial.print("TUBE_STARTPATTERN_ODD: ");
                    Serial.println(pin);
                #endif

                uint8_t value = startPattern[patternIndex];
                if (pin) {
                    if (startPatternPwm)
                        analogWrite(pin, value);
                    else 
                        digitalWrite(pin, value);
                }
                timer.set(startPatternFrequence);
                return;
            }
            case TUBE_START : {
                timer.set(startDelay);
                return;
            }
            case TUBE_END : {
                timer.set(endDelay);
                return;
            }
        }
    }
    
    /*
     * Check Timer and set to next steps
     */

    if (timer.check()) {
        #ifdef DEBUG
            Serial.print("timer checked: ");
            Serial.println(pin);
        #endif

        switch (statusIs) {
            case TUBE_START : {
                // End of start delay
                if (startPattern) {
                    statusShould = TUBE_STARTPATTERN_EVEN;
                    patternIndex = 0;
                }
                else { 
                    statusShould = TUBE_GLOW;
                }
                break;
            }
            case TUBE_END : {
                // End of end delay
                statusShould = TUBE_OFF;
                break;
            }
            case TUBE_GLOW : {
                // End of glowing
                statusShould = TUBE_FAILURE;
                break;
            }
            case TUBE_FAILURE : {
                // End of failure
                if (restartPattern) {
                    statusShould = TUBE_RESTARTPATTERN_EVEN;
                    patternIndex = 0;
                }
                else { 
                    statusShould = TUBE_GLOW;
                }
                break;
            }
            /* 
            * Um das Programmiermuster konsistent zu halten wurden, für die Pattern 2 Status verwendet,
            * da der obere Teil dieser Funktion nur auf Statusänderungen reagiert
            */
            case TUBE_RESTARTPATTERN_EVEN : {
                // End of restart Pattern with even index
                patternIndex++;
                if (patternIndex >= restartPatternSize) {
                    statusShould = TUBE_GLOW;
                } else {
                    statusShould = TUBE_RESTARTPATTERN_ODD;
                }
                break;
            }
            case TUBE_RESTARTPATTERN_ODD : {
                // End of restart Pattern with odd index
                patternIndex++;
                if (patternIndex >= restartPatternSize) {
                    statusShould = TUBE_GLOW;
                } else {
                    statusShould = TUBE_RESTARTPATTERN_EVEN;
                }
                break;
            }
            case TUBE_STARTPATTERN_EVEN : {
                // End of start Pattern with even index
                patternIndex++;
                if (patternIndex >= startPatternSize) {
                    statusShould = TUBE_GLOW;
                } else {
                    statusShould = TUBE_STARTPATTERN_ODD;
                }
                break;
            }
            case TUBE_STARTPATTERN_ODD : {
                // End of start Pattern with odd index
                patternIndex++;
                if (patternIndex >= startPatternSize) {
                    statusShould = TUBE_GLOW;
                } else {
                    statusShould = TUBE_STARTPATTERN_EVEN;
                }
                break;
            }
        }
    }
}
