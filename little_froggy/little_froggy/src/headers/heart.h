#ifndef HEART_H
#define HEART_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Heart{
private:
	Texture texture;
public:
	Sprite sprite;
	FloatRect rect;
	Heart();
	Heart(Texture &image);
	void set_full();
	void set_empty();
	void update();
	void draw(RenderWindow &window);
};
#endif