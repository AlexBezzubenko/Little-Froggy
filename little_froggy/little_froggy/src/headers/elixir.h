/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef ELIXIR_H
#define ELIXIR_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Elixir{
public:
	Elixir();
	Elixir(Texture &image);
	FloatRect get_rect();
	void update();
	void set_current_position(float curr_pos_x, float curr_pos_y);
	void draw(RenderWindow &window);
private:
	FloatRect rect;
	Sprite sprite;
};
#endif