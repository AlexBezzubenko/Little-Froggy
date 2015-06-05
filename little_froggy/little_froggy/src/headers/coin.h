/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef COIN_H
#define COIN_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Coin{
public:
	Coin();
	Coin(Texture &image);
	FloatRect get_rect();
	void set_coordinates(float left, float top);
	void update();
	void draw(RenderWindow &window);
private:
	Sprite sprite;
	FloatRect rect;
};
#endif