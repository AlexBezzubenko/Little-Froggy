/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include "headers/heart.h"
#include "headers/consts.h"

Heart::Heart(){
}
Heart::Heart(Texture &image){
	sprite.setTexture(image);	
	rect = FloatRect(100, 10, 44, 44);
	sprite.setTextureRect(IntRect(372, 9, 44, 44));
}

void Heart::set_full(){
	sprite.setTextureRect(IntRect(326, 9, 44, 44));
}
void Heart::set_empty(){
	sprite.setTextureRect(IntRect(372, 9, 44, 44));
}
void Heart::set_rect_left(float left){
	rect.left = left;
}
FloatRect Heart::get_rect(){
	return rect;
}
void Heart::update(){
	sprite.setPosition(rect.left, rect.top);
}
void Heart::draw(RenderWindow &window){
	window.draw(sprite);
}