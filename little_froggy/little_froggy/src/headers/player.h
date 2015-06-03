#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
	float acceleration_x, acceleration_y;
public:
	void set_acceleration_x(float dx);
	float get_acceleration_x();
	void change_acceleration_x(float dx);
	void set_acceleration_y(float dy);
	float get_acceleration_y();
	void change_acceleration_y(float dy);
	Vector2i p1, p2;
	Vector2i mouth;
	FloatRect rect;
	FloatRect mouth_rect;
	bool onground;
	bool on_tongue;
	bool tongue_out;
	Sprite sprite;
	Sprite mouth_sprite;
	Player(Texture &image);
	Player();
	void update(float time);
	void Collision(int dir);
	void draw(RenderWindow &window);
	void respawn();
};
#endif