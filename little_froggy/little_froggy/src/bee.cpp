#include "headers/bee.h"
#include "headers/consts.h"
Bee::Bee(){
};
Bee::Bee(Texture &image, const IntRect intrects[]){
	for (int i = 0; i < 6; i++){
		this->intrects[i] = intrects[i];
	}
	sprite.setTexture(image);
	rect = FloatRect(400, 300, 60, 60);
	sprite.setTextureRect(this->intrects[0]);
	
	acceleration_x = 0.04;
	current_frame = 0;
}
