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

void Tongue::update(){
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}

void Tongue::draw(RenderWindow &window){
	window.draw(sprite);
}