#ifndef CLOUD_H
#define CLOUD_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Cloud{
public:
	Cloud();
	Cloud(Texture &image, int type);
	void update(float time);
	void draw(RenderWindow &window);
private:
	Texture texture;
	Sprite sprite;
	FloatRect rect;
	double acceleration_x = 0.1;
};
#endif