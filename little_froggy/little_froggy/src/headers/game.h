/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "headers/player.h"
#include "headers/arrow.h"
#include "headers/platform.h"
#include "headers/coin.h"
#include "headers/consts.h"
#include "headers/tongue.h"
#include "headers/fly.h"
#include "headers/floor.h"
#include "headers/heart.h"
#include "headers/elixir.h"
#include "headers/strawberry.h"
#include "headers/menu.h"
#include "headers/cloud.h"
#include "headers/sun.h"

const IntRect INTRECT_PLATS_FLY[6] = {
	IntRect(334, 57, 56, 58),
	IntRect(390, 57, 60, 58),
	IntRect(450, 57, 60, 58),
	IntRect(334 + 56, 57, -56, 58),
	IntRect(390 + 60, 57, -60, 58),
	IntRect(450 + 60, 57, -60, 58)
};
const IntRect INTRECT_PLATS_BEE[6] = {
	IntRect(128 + 59, 130, -59, 58),
	IntRect(188 + 63, 130, -63, 58),
	IntRect(251 + 56, 132, -56, 58),
	IntRect(128, 130, 59, 58),
	IntRect(188, 130, 63, 60),
	IntRect(251, 132, 56, 62)
};

class Game {
public:
	Game();
	void run();
	void object_update(float time);
	void processEvents(float time);
	void render();
	void GameOver();
	RenderWindow window;

private:
	bool game_is_running;
	bool game_over;

	int score;
	int highscore;
	int lifes_count;
	int game_mode;
	int game_speed = 400;

	const int DELTA_ANGLE_ORIGINAL = -0.08;
	float delta_angle = -0.08;
	float left_angle_border = 89;		// first value
	float right_angle_border = 271;
	float current_angle;
	
	Menu menu;
	Music music;
	Music game_over_music;
	Player frog;
	Arrow arrow;
	Tongue tongue;
	Fly fly;
	Fly bee;
	Heart hearts[HEARTS_COUNT];
	Strawberry bonus_strawberry;
	Elixir bonus_elixir;
	Sun sun;

	Coin coin[COIN_COUNT];
	Cloud clouds[CLOUDS_COUNT];
	Floor floor_[FLOOR_COUNT];

	Clock clock;
	
	RectangleShape rectangle;
	Texture *game_texture;
	Texture *background;
	Texture *menu_texture;

	FloatRect rect;
	Sprite sprite_map;

	Text game_over_text;
	Text reset_text;
	Text score_text;
	Text highscore_text;
	Text new_highscore_text;
	Font font;
};

#endif