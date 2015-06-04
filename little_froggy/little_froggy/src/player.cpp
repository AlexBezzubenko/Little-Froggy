#include "headers/player.h"
#include "headers/consts.h"

Player::Player(){		// constructor
}
Player::Player(Texture &image) {		// constructor
	
	sprite.setTexture(image);
	rect = FloatRect(250, 100, 90*0.9, 110*0.9); // 87
	sprite.setTextureRect(IntRect(125, 4, 90, 110));
	sprite.setScale(0.9, 0.9);
	mouth_sprite.setTexture(image);
	mouth_rect = FloatRect(250, 100, 40, 10); 
	mouth_sprite.setTextureRect(IntRect(430, 0, 40, 10));

	acceleration_x = 0;
	acceleration_y = 0;
	on_tongue = false;
	tongue_out = false;
	alive = true;
}


void Player::set_acceleration_x(float dx){
	this->acceleration_x = dx;
}
float Player::get_acceleration_x(){
	return acceleration_x;
}
void Player::change_acceleration_x(float dx){
	this->acceleration_x += dx;
}
void Player::set_acceleration_y(float dy){
	this->acceleration_y = dy;
}
float Player::get_acceleration_y(){
	return acceleration_y;
}
void Player::change_acceleration_y(float dy){
	this->acceleration_y += dy;
}

FloatRect Player::get_rect(){
	return rect;
}
bool Player::is_on_tongue(){
	return on_tongue;
}
bool Player::is_tongue_out(){
	return tongue_out;
}
bool Player::is_on_ground(){
	return onground;
}
void Player::set_on_tongue(bool state){
	on_tongue = state;
}
void Player::set_tongue_out(bool state){
	tongue_out = state;
}
void Player::set_on_ground(bool state){
	onground = state;
}
void Player::set_alive(bool state){
	alive = state;
}
Vector2i Player::get_mouth(){
	return mouth;
}
void Player::set_point_1(Vector2i point){
	point_1 = point;
}
void Player::set_point_2(Vector2i point){
	point_2 = point;
}
Vector2i Player::get_point_1(){
	return point_1;
}
Vector2i Player::get_point_2(){
	return point_2;
}
void Player::set_rect_left(float left){
	rect.left = left;
}
void Player::set_rect_top(float top){
	rect.top = top;
}
void Player::kill(){
	onground = true;
	alive = false;
	set_acceleration_x(0);
	set_acceleration_y(0);
	if (!on_tongue){
		sprite.setTextureRect(IntRect(220, 0, 100, 125));
	}
}
void Player::update(float time) {
	
	rect.left += acceleration_x*time;

	Collision(0);

	if (!onground){
		acceleration_y += 0.0005*time;
	} //gravity
	
	rect.top += acceleration_y*time;
	if (!on_tongue) onground = false;
	
	Collision(1);

	if (acceleration_y < 0) { 
		rect.height = 130 * 0.9;  
		sprite.setTextureRect(IntRect(28, 4, 90, 130)); 
		sprite.setScale(0.9, 0.9); 
	}
	if (acceleration_y == 0 && alive) { 
		rect.height = 110*0.9; 
		sprite.setTextureRect(IntRect(125, 4, 90, 110)); 
		sprite.setScale(0.9, 0.9);
		set_acceleration_x(0);
	}
	
	if (rect.left < border) {
		if (!on_tongue) {
			set_acceleration_x(0);
			rect.left = border;
		}
	}
	if (onground && !on_tongue){  
		set_acceleration_x(0); 
		set_acceleration_y(0.001); 
	}
	for (int i = 0; i < PLATS_COUNT; i++) {
		if (onground && rect.left + rect.width > plats[i].get_rect().left
			&& rect.left < plats[i].get_rect().left + plats[i].get_rect().width){
			plats[i].set_frog_on(true);
			if (plats[i].get_type() == 2 && !on_tongue){
				set_acceleration_x(plats[i].get_acceleration_x());
			}
		}
		else {
			plats[i].set_frog_on(false);
			}
	}
	
	mouth.x = rect.left + rect.width / 2;
	mouth.y = rect.top + 45;
	mouth_rect.left = mouth.x - mouth_rect.width / 2;
	mouth_rect.top = mouth.y - mouth_rect.height / 2;
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
	mouth_sprite.setPosition(mouth_rect.left - offset_x, mouth_rect.top - offset_y);
}

void Player::Collision(int dir) {
	for (int i = 0; i < PLATS_COUNT; i++) {
		if (rect.intersects(plats[i].get_help_rect())) {
			if (acceleration_x > 0 && dir == 0) {
				rect.left = plats[i].get_help_rect().left - rect.width;
				set_acceleration_x(0);
			}
			if (acceleration_x < 0 && dir == 0) {
				rect.left = plats[i].get_help_rect().left + plats[i].get_help_rect().width;
				set_acceleration_x(0);
			}
			if (acceleration_y > 0 && dir == 1) {
				rect.top = plats[i].get_help_rect().top - rect.height;
				set_acceleration_y(0);
				onground = true;
			}
			if (acceleration_y < 0 && dir == 1) {
				rect.top = plats[i].get_rect().top + plats[i].get_rect().height;
				set_acceleration_y(0);
				set_acceleration_x(0);
				onground = false;
			}			
		}
	}
}

void Player::respawn(){
	alive = true;
	sprite.setTextureRect(IntRect(125, 4, 90, 110));
	
	int available = 0;
	for (int i = 0; i < PLATS_COUNT; i++){
		if (plats[i].get_type() != 4 && plats[i].get_rect().left > border
			&& plats[i].get_rect().top < SCREEN_SIZE.y){
			available = i;
			break;
		}
	}

	rect.left = plats[available].get_rect().left + 20;
	rect.top = plats[available].get_rect().top - 100;
	if (rect.left > border + SCREEN_SIZE.x / 2){
		offset_x = rect.left - SCREEN_SIZE.x / 2;
	}
}

void Player::draw(RenderWindow &window){
	window.draw(sprite);
	if (on_tongue || tongue_out){
		window.draw(mouth_sprite);
	}
}



	
			
		
