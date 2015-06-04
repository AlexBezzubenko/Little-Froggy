/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

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
	if (rect.left > border + SCREEN_SIZE.x - offset_x
		){
		rect.left = border - rect.width - offset_x;
	}
	rect.left += acceleration_x * time;
	sprite.setPosition(rect.left , rect.top );
}

void Cloud::draw(RenderWindow &window){
	window.draw(sprite);
}