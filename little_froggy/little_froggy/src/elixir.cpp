/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include "headers/elixir.h"
#include "headers/consts.h"

Elixir::Elixir(){
}
Elixir::Elixir(Texture &image){
	sprite.setTexture(image);
	rect = FloatRect(100, 100, 38, 46);
	sprite.setTextureRect(IntRect(383, 134, 38, 46));
}
FloatRect Elixir::get_rect(){
	return rect;
}
void Elixir::update(){
	if (int(border) % 2000 == 0){
		rect.left = border + SCREEN_SIZE.x;
		rect.top = 200 + rand() % 150;
	} // replacing for each 2000 pixels
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}
void Elixir::set_current_position(float curr_pos_x, float curr_pos_y){
	rect.left = curr_pos_x;
	rect.top = curr_pos_y;
}

void Elixir::draw(RenderWindow &window){
	window.draw(sprite);
}