#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
public:
	
	void set_acceleration_x(float dx);
	float get_acceleration_x();
	void change_acceleration_x(float dx);
	void set_acceleration_y(float dy);
	float get_acceleration_y();
	void change_acceleration_y(float dy);

	Player();
	Player(Texture &image);
	FloatRect get_rect();
	bool is_on_tongue();
	bool is_tongue_out();
	bool is_on_ground();
	bool is_alive();
	void set_on_tongue(bool state);
	void set_tongue_out(bool state);
	void set_on_ground(bool state);
	void set_alive(bool state);
	Vector2i get_mouth();
	void set_point_1(Vector2i point);
	void set_point_2(Vector2i point);
	Vector2i get_point_1();
	Vector2i get_point_2();
	void set_rect_top(float top);
	void set_rect_left(float left);
	void kill();
	void update(float time);
	void Collision(int dir);
	void draw(RenderWindow &window);
	void respawn();
private:
	float acceleration_x, acceleration_y;
	bool onground;
	bool on_tongue;
	bool tongue_out;
	bool alive;

	Vector2i point_1, point_2;
	Vector2i mouth;
	FloatRect rect;
	FloatRect mouth_rect;

	Sprite sprite;
	Sprite mouth_sprite;
};
#endif