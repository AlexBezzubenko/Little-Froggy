#ifndef FLOOR_H
#define FLOOR_H
#include <SFML/Graphics.hpp>
using namespace sf;
class Floor{
public:
	Floor();
	Floor(Texture &image);
	FloatRect get_rect();
	void set_rect_left(float left);
	void set_rect_top(float top);
	void update();
	void draw(RenderWindow &window);
private:
	Sprite sprite;
	FloatRect rect;
};
#endif