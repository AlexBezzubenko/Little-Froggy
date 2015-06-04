#include "headers/sun.h"
#include "headers/consts.h"

Sun::Sun(){
}
Sun::Sun(Texture &image){
	sprite.setTexture(image);
	rect = FloatRect(-226, SCREEN_SIZE.y - 50, 226, 226);
	sprite.setTextureRect(IntRect(510, 320, 287, 287));
	sprite.setScale(0.8f, 0.8f);
	sprite.setOrigin(141, 141);
}

void Sun::update(float time){
	if ( rect.top > SCREEN_SIZE.y - 50){
		rect.left = border - rect.width - offset_x;
		rect.top = SCREEN_SIZE.y - 50 ;
		acceleration_y = 0.012;
	}
	
	rect.left += acceleration_x * time;
	rect.top -= acceleration_y * time;
	acceleration_y -= 0.0001*time / 800;

	sprite.setRotation(sprite.getRotation() + time * rotation);
	sprite.setPosition(rect.left , rect.top );
}

void Sun::draw(RenderWindow &window){
	window.draw(sprite);
}