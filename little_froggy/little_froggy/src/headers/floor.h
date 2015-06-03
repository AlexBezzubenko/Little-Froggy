#ifndef FLOOR_H
#define FLOOR_H
#include <SFML/Graphics.hpp>
using namespace sf;
class Floor{

public:
	Sprite sprite;
	FloatRect rect;
	Floor();
	Floor(Texture &image);
	void update();
	void draw(RenderWindow &window);
};
#endif