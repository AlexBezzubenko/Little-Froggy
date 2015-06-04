#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
class Platform{
public:
	Platform();
	Platform(Texture &image);
	void set_frog_on(bool state);
	float get_acceleration_x();
	int get_type();
	void set_type(int type);
	FloatRect get_help_rect();
	FloatRect get_rect();
	void set_rect_left(float left);
	void update(float time);
	void draw(RenderWindow &window);
private:
	bool crashed;
	bool frog_on;
	int type;
	float acceleration_x, acceleration_y;
	FloatRect help_rect;
	FloatRect rect;
	float timer;
	Clock clock;
	Sprite sprite;
};
#endif