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
		rect.left += screen_size.x + rand() % 100;
		int position_y = rand() % 250 + 100;
		rect.top = position_y;
	}

	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}

void Coin::draw(RenderWindow &window){
	window.draw(sprite);
}