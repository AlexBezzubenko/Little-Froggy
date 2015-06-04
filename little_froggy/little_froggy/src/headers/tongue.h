/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TONGUE_H
#define TONGUE_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Tongue{
public:
	Tongue();
	Tongue(Texture &image);
	int get_original_height();
	Vector2i get_dot();
	void set_dot(Vector2i point);
	FloatRect get_rect();
	void set_rect_left(float left);
	void set_rect_top(float top);
	void set_rect_height(float height);
	Sprite get_sprite();
	void set_sprite_scale(float scale_x, float scale_y);
	void set_rotation(float angle);
	void update();
	void draw(RenderWindow &window);
private:
	int original_height = 144;
	FloatRect rect;
	Vector2i dot;
	Sprite sprite;
};
#endif