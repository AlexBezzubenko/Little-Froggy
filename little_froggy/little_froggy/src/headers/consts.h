/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef CONSTS_H
#define CONSTS_H
#include "headers/platform.h"
#include "headers/floor.h"
#include "headers/coin.h"

extern float offset_x ;
extern float offset_y ;
extern float border;
extern int score;

const int PLATS_COUNT = 4;
const int FLOOR_COUNT = 8;
const int COIN_COUNT = 4;
const int CLOUDS_COUNT = 2;
const int HEARTS_COUNT = 3;

extern Platform plats[PLATS_COUNT];

const struct SCREEN_SIZE{
	int x = 1366;
	int y = 768;
} SCREEN_SIZE;

#endif