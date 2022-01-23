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

class TaTTube : public TaTActor
{
    public:

        TaTTube();
        TaTTube(uint8_t pin);

        void init(uint8_t pin);

        void setDelay(uint32_t start, uint32_t end = 0);
        void setRandomDelay(uint32_t startmax, uint32_t endmax = 0);
        void setRandomDelay(uint32_t startmin, uint32_t startmax, uint32_t endmin, uint32_t endmax);
        void setFailure(uint32_t interval, uint32_t variation = 0, uint32_t duration = 10);

        void on();
        void off();

        void tick();

    protected:

        enum TAT_TUBESTATES { TUBE_OFF, TUBE_START, TUBE_IGNITION_ON, TUBE_IGNITION_OFF, TUBE_ON, TUBE_FAILURE, TUBE_END };
        TAT_TUBESTATES statusShould = TUBE_OFF;
        TAT_TUBESTATES statusIs = TUBE_OFF;

        uint32_t startDelay = 0;
        uint32_t endDelay = 0;
        uint32_t randomStartDelayMin = 0;
        uint32_t randomStartDelayMax = 0;
        uint32_t randomEndDelayMin = 0;
        uint32_t randomEndDelayMax = 0;
        uint32_t failsInterval = 0;     // average fail interval in seconds, 0=no fails
        uint32_t failsVariation = 0;    // fail variation, 0=exact
        uint32_t failsDuration = 0;     // duration of the failure

        TaTTimer timer;

};

#endif