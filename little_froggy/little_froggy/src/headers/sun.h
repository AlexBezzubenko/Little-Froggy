#ifndef SUN_H
#define SUN_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Sun{
public:
	Sun();
	Sun(Texture &image);
	void update(float time);
	void draw(RenderWindow &window);
private:
	Sprite sprite;
	FloatRect rect;
	float acceleration_x = 0.01;
	float acceleration_y = 0.012;
	float gravity = 0.005;
	float rotation = 0.01;
};
#endif