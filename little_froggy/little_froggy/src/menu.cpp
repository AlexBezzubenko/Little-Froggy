#include "headers/menu.h"
#include "headers/consts.h"

Menu::Menu(Texture &image){
	sprite.setTexture(image);
	rect2 = FloatRect(0, 0, screen_size.x, screen_size.y);
	sprite.setTextureRect(IntRect(950 + 70, 260 + 220, -70, -220));
	sprite.setScale(0.001f, 0.0001f);
}
Menu::Menu(){
	rect.setPosition(0,0);
	float x = screen_size.x;
	float y = screen_size.y;
	rect.setSize(sf::Vector2f(screen_size.x, screen_size.y));
	rect.setFillColor(sf::Color(100, 250, 50));

	//rect = FloatRect(0, 0, screen_size.x, screen_size.y);
	
}

void Menu::show(){

}
void Menu::update(){
	//sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
}