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
#include "headers/bee.h"
#include "headers/heart.h"
#include "headers/elixir.h"
#include "headers/strawberry.h"
#include "headers/menu.h"
#include "headers/cloud.h"
#include "headers/sun.h"

const IntRect intrect_plats_fly[6] = {
	IntRect(334, 57, 56, 58),
	IntRect(390, 57, 60, 58),
	IntRect(450, 57, 60, 58),
	IntRect(334 + 56, 57, -56, 58),
	IntRect(390 + 60, 57, -60, 58),
	IntRect(450 + 60, 57, -60, 58)
};
const IntRect intrect_plats_bee[6] = {
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
	int lifes_count;
	int game_mode;
	int game_speed = 400;
	const int delta_angle_original = -0.08;
	float delta_angle = -0.08;
	float left_angle_border = 89;		// first value
	float right_angle_border = 271;
	
	Menu menu;
	Music music;
	Music game_over_music;
	Player frog;
	Arrow arrow;
	Tongue tongue;
	Fly fly;
	Bee bee;
	Heart hearts[hearts_count];
	Strawberry *bonus_strawberry;
	Elixir *bonus_elixir;

	Coin coin[coin_count];
	Cloud clouds[clouds_count];
	Sun sun;
	Floor floor_[floor_count];

	Clock clock;
	
	RectangleShape rectangle;
	Texture *game_texture;
	Texture *background;
	Texture *menu_texture;

	FloatRect rect;
	Sprite s_map;

	Text text;
	Text score_text;
	Font font;
};

#endif