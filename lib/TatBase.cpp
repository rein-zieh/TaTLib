/*
 * TaTBase.cpp
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

#include "TaTBase.h"

/*
 * TaTActor
 *
 * Base class for all single wired actors
 *
 */
TaTActor::TaTActor() {
}

TaTActor::TaTActor(uint8_t pin) {
    init(pin);
}

void TaTActor::init(uint8_t pin) {
    this->pin = pin;
}

/*
 * TaTSensor
 *
 * Base class for all single wired sensors
 *
 */
TaTSensor::TaTSensor() {
    nr_actors = 0;
}

TaTSensor::TaTSensor(uint8_t pin) {
    init(pin);
}

void TaTSensor::init(uint8_t pin) {
    nr_actors = 0;
    this->pin = pin;
}

void TaTSensor::on() {
    for(int i =  0; i < nr_actors; i++) {
        this->actors[i]->on();
    }
    //actorState = HIGH;
}

void TaTSensor::off() {
    for(int i =  0; i < nr_actors; i++) {
        this->actors[i]->off();
    }
    //actorState = LOW;
}

void TaTSensor::connect(TaTActor *actor) {
    if (nr_actors < TAT_MAX_ACTORS_PER_BUTTON) {
        this->actors[nr_actors++] = actor;
    }
}

/*
 * TaTTimer
 *
 * Base class for all timer
 *
 */
TaTTimer::TaTTimer(uint32_t duration) {
    set(duration);
}

void TaTTimer::set(uint32_t duration) {
    this->duration = duration;
    last = millis();
}


boolean TaTTimer::check() {
    return (millis() - last >= duration);
}

boolean TaTTimer::checkAndRepeat() {
    if (millis() - last < duration) {
        return false;
    }
    last = millis();
    return true;  
}

boolean TaTTimer::checkAndSet(uint32_t duration = 0) {
    if (millis() - last < this->duration) {
        return false;
    }
    last = millis();
    this->duration = duration;
    return true;  
}