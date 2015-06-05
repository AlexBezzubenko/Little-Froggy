/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef CLOUD_H
#define CLOUD_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Cloud{
public:
	Cloud();
	Cloud(Texture &image, int type);
	void update(float time);
	void draw(RenderWindow &window);
private:
	Sprite sprite;
	FloatRect rect;
	double acceleration_x = 0.1;
};
#endif