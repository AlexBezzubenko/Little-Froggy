#ifndef ARROW_H
#define ARROW_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Arrow{
public:
	FloatRect rect;
	Sprite sprite;
	Arrow();
	Arrow(Texture &image); 
	void update();
	void draw(RenderWindow &window);
private:
};
#endif