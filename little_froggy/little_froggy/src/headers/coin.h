#ifndef COIN_H
#define COIN_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Coin{
private:
	Texture texture;
	Sprite sprite;
public:
	FloatRect rect;
	Coin();
	Coin(Texture &image);
	void update();
	void draw(RenderWindow &window);
};
#endif