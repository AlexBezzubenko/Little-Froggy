#include "headers/elixir.h"
#include "headers/consts.h"

Elixir::Elixir(){
}
Elixir::Elixir(Texture &image){
	sprite.setTexture(image);
	rect = FloatRect(100, 100, 38, 46);
	sprite.setTextureRect(IntRect(383, 134, 38, 46));
}

void Elixir::update(){
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}
void Elixir::set_current_position(float curr_pos_x, float curr_pos_y){
	rect.left = curr_pos_x;
	rect.top = curr_pos_y;
}

void Elixir::draw(RenderWindow &window){
	window.draw(sprite);
}