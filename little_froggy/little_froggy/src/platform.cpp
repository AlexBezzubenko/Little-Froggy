/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include "headers/platform.h"
#include "headers/consts.h"

Platform::Platform(){
}
Platform::Platform(Texture &image){	
	type = rand() % 5;  
	acceleration_x = 0;
	acceleration_y = 0;
	timer = 0;
	sprite.setTexture(image);
	rect = FloatRect(0, SCREEN_SIZE.y / 2, 125, 60);
	help_rect = rect;
	help_rect.top += 30;
	help_rect.height -= 30;
	crashed = false;
	frog_on = false;
	sprite.setTextureRect(IntRect(275, 205, 125, 60));
}

void Platform::set_frog_on(bool state){
	frog_on = state;
}
float Platform::get_acceleration_x(){
	return acceleration_x;
}
int Platform::get_type(){
	return type;
}
void Platform::set_type(int type){
	this->type = type;
}
FloatRect Platform::get_help_rect(){
	return help_rect;
}
FloatRect Platform::get_rect(){
	return rect;
}
void Platform::set_rect_left(float left){
	rect.left = left;
}
void Platform::update(float time){

	if (rect.left + rect.width < border){	
		for (int i = 0; i < 4; i++){
			if (plats[i].rect == rect){
				
				int previous = i - 1;
				if (i == 0) {
					previous = 3;
				}
				type = rand() % 5;
				while (plats[previous].type == type){
					type = rand() % 5;
				}
				rect.left = plats[previous].rect.left + 3 * rect.width;
				/*if (rect.left + rect.width < border + SCREEN_SIZE.x){
					rect.left = border + SCREEN_SIZE.x;
				}*/
				crashed = false;
				timer = 0;
				frog_on = false;
			}
		}
		rect.top = SCREEN_SIZE.y / 2 - 50 + rand() % 100;
		
		acceleration_x = acceleration_y = 0;
		if (type == 2) acceleration_x = -0.03;
	}
	if (type == 0){
		sprite.setTextureRect(IntRect(275, 205, 125, 60));
		acceleration_x = 0;
		acceleration_y = 0;
	}
	if (type == 1){
		sprite.setTextureRect(IntRect(275, 205, 125, 60));
		if (rect.top < 100){
			acceleration_y = 0.03;
		}
		if (rect.top >= SCREEN_SIZE.y / 2){
			acceleration_y = -0.03;
		}
	}

	if (type == 2){
		sprite.setTextureRect(IntRect(275, 205, 125, 60));
		for (int i = 0; i < 4; i++){
			if (plats[i].rect == rect){
				int next = i + 1;

				if (i == 3){
					next = 0;
				};

				if (rect.left + rect.width > plats[next].rect.left - 10 
					&& abs(rect.left - plats[next].rect.left) < rect.width + 20){
					acceleration_x = -0.03;
				}
				if (rect.left + rect.width > border + SCREEN_SIZE.x){
					acceleration_x = -0.03;
				}

				int previous = i - 1;
				if (i == 0) {
					previous = 3;
				}

				if (rect.left < plats[previous].rect.left + plats[previous].rect.width + 10 
					&& abs(rect.left - plats[previous].rect.left) < rect.width + 20){
					acceleration_x = 0.03;
				}
				if ( rect.left < border){
					acceleration_x = 0.03;
				}
			}
		}
	}
	if (type == 3){
		acceleration_x = 0;
		acceleration_y = 0;
		
		if (!crashed){
			sprite.setTextureRect(IntRect(0, 276, 125, 60));
		}
		  
		
		if (frog_on){
			crashed = true;
			sprite.setTextureRect(IntRect(140, 210, 125, 60));
			float time1 = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time1;
			std::cout << timer << "   " << std::endl;
		}
			else
		{
				clock.restart();
		}	
		if (timer > 3 && crashed){
			rect.top += SCREEN_SIZE.y;
			timer = 0;
		}

	}
	if (type == 4){
		acceleration_x = 0;
		acceleration_y = 0;
		sprite.setTextureRect(IntRect(136, 275, 125, 60));
		rect.top = 0 - (rect.height - help_rect.height);
	}
	rect.top += acceleration_y*time;
	rect.left += acceleration_x*time;
	
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
	help_rect = rect;
	help_rect.top += 30;
	help_rect.height -= 30;
}

void Platform::draw(RenderWindow &window){
	window.draw(sprite);
}