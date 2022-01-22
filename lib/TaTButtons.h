/*
 * TaTPushButton.h
 * 
 * Class for a Push Button
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

#ifndef TaTButtons_h
#define TaTButtons_h

#include "TaTBase.h"

#define TAT_TREMOR 40

class TaTButton : public TaTSensor
{
    protected:
        uint8_t prevRead = LOW;
        uint32_t lastTime = 0;
        uint32_t tremor = TAT_TREMOR;

    public:
        TaTButton();
        TaTButton(uint8_t pin, uint32_t tremor = TAT_TREMOR);

        void init(uint8_t pin, uint32_t tremor = TAT_TREMOR);
        void setTremor(uint32_t tremor);
        void tick();
};

class TaTButtonInv : public TaTButton
{
    public:
        TaTButtonInv();
        TaTButtonInv(uint8_t pin, uint32_t tremor = TAT_TREMOR);

        void tick();
};

class TaTButtonOnOff : public TaTButton
{
    public:
        TaTButtonOnOff();
        TaTButtonOnOff(uint8_t pin, uint32_t tremor = TAT_TREMOR);
        void tick();

    private:
        // Variables
        uint8_t buttonState = LOW;
};

#endif