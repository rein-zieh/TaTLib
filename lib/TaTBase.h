/*
 * TaTBase.h
 * 
 * Base classes for the TaT-Toolkit
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

#ifndef TaTBase_h
#define TaTBase_h

#include "Arduino.h"

#define TAT_MAX_ACTORS_PER_BUTTON 16

class TaTActor
{
    public:

        TaTActor();
        TaTActor(uint8_t pin);

        void init(uint8_t pin);     //wire actor with pin

        virtual void on();          //switch actor on
        virtual void off();         //switch actor off

        virtual void tick();        //ticking, to call in the loop function 

    protected:

        uint8_t pin;                // wired pin

};

class TaTSensor
{
    public:

        TaTSensor();
        TaTSensor(uint8_t pin);

        void init(uint8_t pin);         //wire sensor with pin

        void connect(TaTActor *actor);  //wire sensor with actor

        virtual void tick();            //ticking, to call in the loop function 

    protected:

        void on();
        void off();

        uint8_t pin;                                    // wired pin
        TaTActor *actors[TAT_MAX_ACTORS_PER_BUTTON];    // array of wired actors
        uint8_t nr_actors;                              // mumber of actors in array

        uint8_t sensorState = LOW;

};

class TaTTimer
{
    public:
        TaTTimer(uint32_t duration = 0);
        
        void set(uint32_t duration = 0);

        boolean check();
        boolean checkAndRepeat();
        boolean checkAndSet(uint32_t duration);
      
    private:
        uint32_t duration;
        uint32_t last;
};

#endif