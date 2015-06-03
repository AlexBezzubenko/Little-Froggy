#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
class Platform{
public:
	int type;
	float dx, dy;
	float middle;
	 
	FloatRect rect;
	FloatRect temp;
	Sprite sprite;
	Clock clock;
	float timer;
	bool crashed;
	bool frog_on;
	Platform(Texture &image);
	Platform();
	void update(float time);
	void draw(RenderWindow &window);
};
#endif