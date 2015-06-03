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
	if (!on_tongue) onground = false; //BOT KOC9lK
	
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
	for (int i = 0; i < plats_count; i++) {
		if (onground && rect.left + rect.width > plats[i].rect.left
			&& rect.left < plats[i].rect.left + plats[i].rect.width){
			plats[i].frog_on = true;
			if (plats[i].type == 2 && !on_tongue){
				 set_acceleration_x(plats[i].dx);
			}
		}
		else {
			plats[i].frog_on = false;
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
	for (int i = 0; i < plats_count; i++) {
		if (rect.intersects(plats[i].temp)) {
			if (acceleration_x > 0 && dir == 0) {
				rect.left = plats[i].temp.left - rect.width;
				set_acceleration_x(0);
			}
			if (acceleration_x < 0 && dir == 0) {
				rect.left = plats[i].temp.left + plats[i].temp.width;
				set_acceleration_x(0);
			}
			if (acceleration_y > 0 && dir == 1) {
				rect.top = plats[i].temp.top - rect.height;
				set_acceleration_y(0);
				onground = true;
			}
			if (acceleration_y < 0 && dir == 1) {
				rect.top = plats[i].rect.top + plats[i].rect.height;
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
	for (int i = 0; i < plats_count; i++){
		if (plats[i].type != 4 && plats[i].rect.left > border
			&& plats[i].rect.top < screen_size.y){
			available = i;
			break;
		}
	}

	rect.left = plats[available].rect.left + 20;
	rect.top = plats[available].rect.top - 100;
	if (rect.left > border + screen_size.x / 2){
		offset_x = rect.left - screen_size.x / 2;
	}
}

void Player::draw(RenderWindow &window){
	window.draw(sprite);
	if (on_tongue || tongue_out){
		window.draw(mouth_sprite);
	}
}



	
			
		
