/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include "headers/fly.h"
#include "headers/consts.h"

Fly::Fly(){
}
Fly::Fly(Texture &image, const IntRect intrects[]){
	for (int i = 0; i < 6; i++){
		this->intrects[i] = intrects[i];
	}
	sprite.setTexture(image);	
	rect = FloatRect(400, 300, 60, 60);
	current_position.x = 400;
	current_position.y = 300;
	sprite.setTextureRect(this->intrects[0]);
	
	acceleration_x = 0.03;
	current_frame = 0;
	eaten = false;
}
FloatRect Fly::get_rect(){
	return rect;
}
void Fly::update(float time){
	if (rect.left + rect.width < border){
		int pos_x = rect.left + SCREEN_SIZE.x + rand() % 1000;
		int pos_y = 200 + rand() % 300;
		set_current_position(pos_x, pos_y);
	}
	if (eaten){
		rect.left += SCREEN_SIZE.x;
		eaten = false;
		current_position.x += SCREEN_SIZE.x;
		acceleration_x = 0.03;
		acceleration_y = 0.03;
	}
		if (rect.left  > current_position.x + 100){
			sprite.setTextureRect(this->intrects[0]);
			acceleration_x = -0.03;
		}
		if (rect.left + rect.width < current_position.x - 100){
			sprite.setTextureRect(this->intrects[3]);
			acceleration_x = 0.03;
		}
		if (acceleration_x < 0){
			current_frame += 0.005*time;
			if (current_frame > 3) current_frame -= 3;
			switch (int(current_frame))
			{
			case 0:
				sprite.setTextureRect(intrects[0]);
				break;
			case 1:
				sprite.setTextureRect(intrects[1]);
				break;
			default:
				sprite.setTextureRect(intrects[2]);
				break;
			}
		}
		if (acceleration_x > 0){
			current_frame += 0.005*time;
			if (current_frame > 3) current_frame -= 3;
			switch (int(current_frame))
			{
			case 0:
				sprite.setTextureRect(intrects[3]);
				break;
			case 1:
				sprite.setTextureRect(intrects[4]);
				break;
			default:
				sprite.setTextureRect(intrects[5]);
				break;
			}
		}
		if (rect.top  < current_position.y - 50){
			acceleration_y = 0.03;
		}
		if (rect.top + rect.height > current_position.y + 50){
			acceleration_y = -0.03;
		}

	rect.top += acceleration_y*time;
	rect.left += acceleration_x*time;

	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}

bool Fly::check_is_inrect(Vector2i dot){
	dot.x += offset_x;
	dot.y += offset_y;
	if (rect.top < dot.y && rect.top + rect.height > dot.y
		&& rect.left < dot.x && rect.left + rect.width > dot.x){
		return true;
	}
	else{
		return false;
	}
}

void Fly::set_current_position(float curr_pos_x, float curr_pos_y){
	this->current_position.x = curr_pos_x;
	this->current_position.y = curr_pos_y;
	this->rect.left = curr_pos_x;
	this->rect.top = curr_pos_y;
	acceleration_x = 0.03;
	eaten = false;
}

void Fly::stop(){
	acceleration_x = 0;
	acceleration_y = 0;
	eaten = true;
}

bool Fly::is_eaten(){
	return eaten;
}

void Fly::draw(RenderWindow &window){
	window.draw(sprite);
}