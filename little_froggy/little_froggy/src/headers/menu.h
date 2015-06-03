#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Menu{
public:
	RectangleShape rect;
	FloatRect rect2;
	Sprite sprite;
	Menu(Texture &image);
	Menu();
	void show();
	void update();
};
#endif