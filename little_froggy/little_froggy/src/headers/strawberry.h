#ifndef Strawberry_H
#define Strawberry_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Strawberry{
public:
	Strawberry();
	Strawberry(Texture &image);
	FloatRect get_rect();
	void update();
	void set_current_position(float curr_pos_x, float curr_pos_y);
	void draw(RenderWindow &window);
private:
	FloatRect rect;
	Sprite sprite;
};
#endif