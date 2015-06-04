/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include "headers/floor.h"
#include "headers/consts.h"

Floor::Floor(){
}
Floor::Floor(Texture &image){		
	sprite.setTexture(image);
	rect = FloatRect(0, SCREEN_SIZE.y - 128, 192, 64);
	sprite.setTextureRect(IntRect(296, 270, 192, 64));
}

FloatRect Floor::get_rect(){
	return rect;
}
void Floor::set_rect_left(float left){
	rect.left = left;
}
void Floor::set_rect_top(float top){
	rect.top = top;
}
void Floor::update(){
	if (rect.left + rect.width < border){
		rect.left += SCREEN_SIZE.x + rect.width;
	}
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}

void Floor::draw(RenderWindow &window){
	window.draw(sprite);
}