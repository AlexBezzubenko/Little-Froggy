/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include "headers/strawberry.h"
#include "headers/consts.h"

Strawberry::Strawberry(){
}
Strawberry::Strawberry(Texture &image){
	sprite.setTexture(image);
	rect = FloatRect(100, 100, 45, 50);
	sprite.setTextureRect(IntRect(333, 132, 44, 49));
}
FloatRect Strawberry::get_rect(){
	return rect;
}
void Strawberry::update(){
	if (int(border) % 3000 == 0){
		rect.left = border + SCREEN_SIZE.x + rand() % 500;
		rect.top = 200 + rand() % 150;
	}
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}
void Strawberry::set_current_position(float curr_pos_x, float curr_pos_y){
	rect.left = curr_pos_x;
	rect.top = curr_pos_y;
}
void Strawberry::draw(RenderWindow &window){
	window.draw(sprite);
}