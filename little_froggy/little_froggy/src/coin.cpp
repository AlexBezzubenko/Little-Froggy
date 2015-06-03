#include "headers/coin.h"
#include "headers/consts.h"

Coin::Coin(){

}
Coin::Coin(Texture &image){
	sprite.setTexture(image);	
	rect = FloatRect(400, 300, 65, 65);
	sprite.setTextureRect(IntRect(420, 200, 65, 65));
}

void Coin::update(){
	if (rect.left + rect.width < border){
		rect.top = screen_size.y;
	}
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}

void Coin::draw(RenderWindow &window){
	window.draw(sprite);
}