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