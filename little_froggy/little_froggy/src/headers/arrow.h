#ifndef ARROW_H
#define ARROW_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Arrow{
public:
	Arrow();
	Arrow(Texture &image); 
	float get_height();
	void set_coordinates(float left, float top);
	void set_scale(float scale_x, float scale_y);
	void set_rotation(float angle);
	void update();
	void draw(RenderWindow &window);
private:
	FloatRect rect;
	Sprite sprite;
};
#endif