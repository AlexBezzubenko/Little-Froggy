#include "headers/cloud.h"
#include "headers/consts.h"

Cloud::Cloud(){
}
Cloud::Cloud(Texture &image, int type){
	sprite.setTexture(image);	
	if (type == 1){
		rect = FloatRect(250, 200, 240, 105);
		sprite.setTextureRect(IntRect(0, 480, 240, 105));
	}
	else {
		rect = FloatRect(50, 50, 285, 125);
		sprite.setTextureRect(IntRect(0, 343, 285, 125));
		acceleration_x /= 2;
	}
}

void Cloud::update(float time){
	if (rect.left > border + screen_size.x - offset_x
		){
		rect.left = border - rect.width - offset_x;
	}
	rect.left += acceleration_x * time;
	sprite.setPosition(rect.left , rect.top );
}

void Cloud::draw(RenderWindow &window){
	window.draw(sprite);
}