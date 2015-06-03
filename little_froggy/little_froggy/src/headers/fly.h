#ifndef FLY_H
#define FLY_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Fly{
protected:
	Texture texture;
	float acceleration_x, acceleration_y;
	Vector2f current_position; // _x, current_position_y;
	float current_frame;
	IntRect intrects[6];
	Sprite sprite;
	bool eaten;
public:
	FloatRect rect;
	Fly();
	Fly(Texture &image, const IntRect intrects[]);
	void set_current_position(float curr_pos_x, float curr_pos_y);
	void stop();
	bool check_is_inrect(Vector2i dot);
	bool is_eaten();
	void update(float time);
	void draw(RenderWindow &window);
};
#endif