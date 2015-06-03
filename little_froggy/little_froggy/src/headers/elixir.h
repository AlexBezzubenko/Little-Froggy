#ifndef ELIXIR_H
#define ELIXIR_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Elixir{
public:
	FloatRect rect;
	Elixir();
	Elixir(Texture &image);
	void update();
	void set_current_position(float curr_pos_x, float curr_pos_y);
	void draw(RenderWindow &window);
private:
	Sprite sprite;
};
#endif