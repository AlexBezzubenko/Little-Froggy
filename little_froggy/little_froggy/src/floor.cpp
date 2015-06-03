#include "headers/floor.h"
#include "headers/consts.h"

Floor::Floor(){
}
Floor::Floor(Texture &image){		
	sprite.setTexture(image);
	rect = FloatRect(0, screen_size.y - 128, 192, 64);
	sprite.setTextureRect(IntRect(296, 270, 192, 64));
}

void Floor::update(){
	if (rect.left + rect.width < border){
		rect.left += screen_size.x + rect.width;
	}
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}

void Floor::draw(RenderWindow &window){
	window.draw(sprite);
}