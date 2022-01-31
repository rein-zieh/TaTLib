/*
 * TaTPattern.h
 * 
 * Collection of pattern examples
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

#ifndef TaTPattern_h
#define TaTPattern_h

const uint8_t TaTPatternAnalogTube[] = {
    0, 220, 40, 10, 0, 0, 0, 0, 0, 0, 
    220, 80, 20, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 180, 210, 230, 255
};

const uint8_t TaTPatternDigitalTube[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0
};

const uint8_t TaTPatternDigitalWelder_1[] = {
    1, 1, 0, 0, 1, 0, 1, 0, 0, 0,
    1, 1, 0, 0, 0, 1, 0, 0, 1, 1,
    0, 1, 1, 0, 0, 1, 1, 1, 0, 1
};

const uint8_t TaTPatternDigitalWelder_2[] = {
    1, 1, 1, 0, 1, 1, 1, 0, 0, 0,
    1, 1, 0, 0, 1, 1, 1, 0, 1, 1,
    0, 1, 1, 0, 1, 1, 1, 1, 0, 1
};

#endif