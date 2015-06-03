#ifndef TONGUE_H
#define TONGUE_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Tongue{
public:
	int original_height = 144;
	FloatRect rect;
	Sprite sprite;
	Texture texture;
	Vector2i dot;
	Tongue();
	Tongue(Texture &image);
	void update();
	void draw(RenderWindow &window);
};
#endif