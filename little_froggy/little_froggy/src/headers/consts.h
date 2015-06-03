#ifndef CONSTS_H
#define CONSTS_H
#include "headers/platform.h"
#include "headers/floor.h"
#include "headers/coin.h"

extern float offset_x ;
extern float offset_y ;
extern float border;
extern int score;

const int plats_count = 4;
const int floor_count = 8;
const int coin_count = 4;
const int clouds_count = 2;
const int hearts_count = 3;

extern Platform plats[plats_count];

const struct screen_size{
	int x = 1366;
	int y = 768;
} screen_size;

#endif