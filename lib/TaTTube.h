/*
 * TaTTube.h
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

#ifndef TaTTube_h
#define TaTTube_h

#include "TaTLed.h"

class TaTTube : public TaTLed
{
    public:

        TaTTube();
        TaTTube(uint8_t pin);

        void setFailure(uint32_t interval, uint32_t variation = 0, uint32_t duration = 10);
        void setRestartPattern(uint8_t *pattern, uint32_t patternSize, uint32_t patternFrequence = 10, bool pwm = false);
        void setStartPattern(uint8_t *pattern, uint32_t patternSize, uint32_t patternFrequence = 10, bool pwm = false);

        void on();
        void off();

        void tick();

        static const uint8_t analogPattern[27];
        static const uint8_t digitalPattern[30];

    protected:

        enum TAT_TUBESTATES { TUBE_OFF, TUBE_START, TUBE_STARTPATTERN_EVEN, TUBE_STARTPATTERN_ODD, TUBE_GLOW, TUBE_FAILURE, TUBE_RESTARTPATTERN_EVEN, TUBE_RESTARTPATTERN_ODD, TUBE_END };
        TAT_TUBESTATES statusShould = TUBE_OFF;
        TAT_TUBESTATES statusIs = TUBE_OFF;

        uint32_t failureInterval = 0;     // average fail interval in seconds, 0=no fails
        uint32_t failureVariation = 0;    // fail variation, 0=exact
        uint32_t failureDuration = 0;     // duration of the failure
        
        uint8_t *restartPattern = NULL;
        uint32_t restartPatternSize = 0;
        uint32_t restartPatternFrequence = 0;
        bool restartPatternPwm = false;
        
        uint8_t *startPattern = NULL;
        uint32_t startPatternSize = 0;
        uint32_t startPatternFrequence = 0;
        bool startPatternPwm = false;
        
        uint32_t patternIndex = 0;

        TaTTimer timer;

};

#endif