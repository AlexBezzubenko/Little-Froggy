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
	if (int(border) % 2000 == 0){
		rect.left = border + screen_size.x;
		rect.top = 200 + rand() % 150;
	}
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}
void Elixir::set_current_position(float curr_pos_x, float curr_pos_y){
	rect.left = curr_pos_x;
	rect.top = curr_pos_y;
}

void Elixir::draw(RenderWindow &window){
	window.draw(sprite);
}