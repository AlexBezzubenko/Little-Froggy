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
	Texture texture;
	Sprite sprite;
	FloatRect rect;
};
#endif