#include "headers/arrow.h"
#include "headers/consts.h"

Arrow::Arrow(){
}
Arrow::Arrow(Texture &image){	
	sprite.setTexture(image);
	rect = FloatRect(500, 400, 70, 220);
	//sprite.setTextureRect(IntRect(950 + 70, 260 + 220, -70, -220));
	sprite.setTextureRect(IntRect(520 + 70, 0 + 220, -70, -220));
	sprite.setScale(0.001f, 0.0001f);
}

void Arrow::update(){
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}

void Arrow::draw(RenderWindow &window){
	window.draw(sprite);
}