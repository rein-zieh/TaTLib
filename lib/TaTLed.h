/*
 * TaTLed.h
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

#ifndef TaTLed_h
#define TaTLed_h

#include "TaTBase.h"

class TaTLed : public TaTActor
{
    public:

        TaTLed();
        TaTLed(uint8_t pin);

        void init(uint8_t pin);

        //void setDelay(uint32_t start, uint32_t end = 0);
        //void setRandomDelay(uint32_t startmax, uint32_t endmax = 0);
        //void setRandomDelay(uint32_t startmin, uint32_t startmax, uint32_t endmin, uint32_t endmax);

        void setStartDelay(uint32_t start, uint32_t variation = 0);
        void setEndDelay(uint32_t end, uint32_t variation = 0);


        void on();
        void off();

        void tick();

    protected:

        enum TAT_LEDSTATES { LED_OFF, LED_START, LED_ON, LED_END };
        TAT_LEDSTATES statusShould = LED_OFF;
        TAT_LEDSTATES statusIs = LED_OFF;

        uint32_t startDelay = 0;
        uint32_t endDelay = 0;
        uint32_t startVariation = 0;
        uint32_t endVariation = 0;
        // uint32_t randomStartDelayMin = 0;
        // uint32_t randomStartDelayMax = 0;
        // uint32_t randomEndDelayMin = 0;
        // uint32_t randomEndDelayMax = 0;

        TaTTimer timer;

};

#endif