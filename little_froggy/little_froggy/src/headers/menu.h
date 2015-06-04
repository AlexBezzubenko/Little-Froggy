#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>

using namespace sf;

const int MENU_STRING_COUNT = 3;

class Menu{
public:
	Menu();
	Menu(Texture &image, Font &font);
	int check_selected(Vector2f point);
	void check_target(Vector2f point);
	void show(RenderWindow &window);
	void update();
private:
	FloatRect rect;
	Sprite sprite;
	Text menu_string[MENU_STRING_COUNT];
};
#endif