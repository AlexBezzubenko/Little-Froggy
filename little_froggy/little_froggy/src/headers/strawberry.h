#ifndef Strawberry_H
#define Strawberry_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Strawberry{
public:
	FloatRect rect;
	Strawberry();
	Strawberry(Texture &image);
	void update();
	void set_current_position(float curr_pos_x, float curr_pos_y);
	void draw(RenderWindow &window);
private:
	Sprite sprite;
};
#endif