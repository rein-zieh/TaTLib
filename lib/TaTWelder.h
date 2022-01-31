/*
 * TaTWelder.h
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

#ifndef TaTWelder_h
#define TaTWelder_h

#include "TaTLed.h"

#define TAT_MAX_PATTERN_FOR_WELDER 16

class TaTWelder : public TaTLed
{
    public:

        TaTWelder();
        TaTWelder(uint8_t pin);

        void addPattern(uint8_t *pattern, uint32_t patternSize, uint32_t patternFrequence = 10, bool pwm = false);
        void setPause(uint32_t pause, uint32_t variation = 0);

        void on();
        void off();

        void tick();

    protected:
    
        enum TAT_WELDERSTATES { WELDER_OFF, WELDER_START, WELDER_PATTERN_EVEN, WELDER_PATTERN_ODD, WELDER_PAUSE, WELDER_END };
        TAT_WELDERSTATES statusShould = WELDER_OFF;
        TAT_WELDERSTATES statusIs = WELDER_OFF;

        uint32_t pause = 0;     // average fail interval in seconds, 0=no fails
        uint32_t pauseVariation = 0;    // fail variation, 0=exact

        uint8_t *pattern[TAT_MAX_PATTERN_FOR_WELDER];
        uint32_t patternSize[TAT_MAX_PATTERN_FOR_WELDER];
        uint32_t patternFrequence[TAT_MAX_PATTERN_FOR_WELDER];
        bool patternPwm[TAT_MAX_PATTERN_FOR_WELDER];
        uint8_t nrPattern = 0;

        uint8_t patternIndex = 0;
        int8_t actualPattern = -1;
};

#endif