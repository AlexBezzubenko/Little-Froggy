/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include "headers/arrow.h"
#include "headers/consts.h"

Arrow::Arrow(){
}
Arrow::Arrow(Texture &image){	
	sprite.setTexture(image);
	rect = FloatRect(500, 400, 70, 220);
	sprite.setTextureRect(IntRect(520 + 70, 0 + 220, -70, -220));
	sprite.setOrigin(rect.width / 2, 0);
	sprite.setScale(0.001f, 0.0001f);
};

float Arrow::get_height(){
	return rect.height;
}
void Arrow::set_coordinates(float left, float top){
	rect.left = left;
	rect.top = top;
}
void Arrow::set_scale(float scale_x, float scale_y){
	sprite.setScale(scale_x, scale_y);
}
void Arrow::set_rotation(float angle){
	sprite.setRotation(angle);
}
void Arrow::update(){
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}

void Arrow::draw(RenderWindow &window){
	window.draw(sprite);
}