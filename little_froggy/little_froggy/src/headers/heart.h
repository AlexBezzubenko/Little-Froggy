/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef HEART_H
#define HEART_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Heart{
public:
	Heart();
	Heart(Texture &image);
	void set_full();
	void set_empty();
	void set_rect_left(float left);
	FloatRect get_rect();
	void update();
	void draw(RenderWindow &window);
private:
	FloatRect rect;
	Sprite sprite;
};
#endif