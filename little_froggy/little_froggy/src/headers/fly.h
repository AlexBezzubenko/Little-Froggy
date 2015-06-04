#ifndef FLY_H
#define FLY_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Fly{
public:
	Fly();
	Fly(Texture &image, const IntRect intrects[]);
	FloatRect get_rect();
	void set_current_position(float curr_pos_x, float curr_pos_y);
	void stop();
	bool check_is_inrect(Vector2i dot);
	bool is_eaten();
	void update(float time);
	void draw(RenderWindow &window);
protected:
	bool eaten;
	float current_frame;
	float acceleration_x, acceleration_y;
	Texture texture;
	Vector2f current_position; 
	IntRect intrects[6];
	FloatRect rect;
	Sprite sprite;
};
#endif