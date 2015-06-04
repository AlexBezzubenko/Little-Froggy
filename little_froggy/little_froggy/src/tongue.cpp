/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include "headers/tongue.h"
#include "headers/consts.h"

Tongue::Tongue(){
}
Tongue::Tongue(Texture &image){
	sprite.setTexture(image);
	rect = FloatRect(1000, 225, 22, 144);
	sprite.setTextureRect(IntRect(0, 0, 22, 144));
	sprite.setScale(0.001f, 0.001f);
	sprite.setOrigin( rect.width / 2, 0);

	dot.x = 0;
	dot.y = 0;
	
	rect.height *= sprite.getScale().y;
}
int Tongue::get_original_height(){
	return original_height;
}
Vector2i Tongue::get_dot(){
	return dot;
}
void Tongue::set_dot(Vector2i point){
	dot = point;
}
FloatRect Tongue::get_rect(){
	return rect;
}
void Tongue::set_rect_left(float left){
	rect.left = left;
}
void Tongue::set_rect_top(float top){
	rect.top = top;
}
void Tongue::set_rect_height(float height){
	rect.height = height;
}
Sprite Tongue::get_sprite(){
	return sprite;
}
void Tongue::set_sprite_scale(float scale_x, float scale_y){
	sprite.setScale(scale_x, scale_y);
}
void Tongue::set_rotation(float angle){
	sprite.setRotation(angle);
}
void Tongue::update(){
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}

void Tongue::draw(RenderWindow &window){
	window.draw(sprite);
}