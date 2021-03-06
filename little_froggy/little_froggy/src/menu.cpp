/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include "headers/menu.h"
#include "headers/consts.h"

Menu::Menu(){
}
Menu::Menu(Texture &image, Font &font){
	sprite.setTexture(image);

	rect = FloatRect(0, 0, SCREEN_SIZE.x, SCREEN_SIZE.y);
	sprite.setTextureRect(IntRect(0, 0, 2048, 1548));
	sprite.setScale(1, 0.5);

	menu_string[0].setString("game Mode: Arrow");
	menu_string[1].setString("game Mode: Keyboard");
	menu_string[2].setString("Exit");

	for (int i = 0; i < MENU_STRING_COUNT; i++){
		menu_string[i].setFont(font);
		menu_string[i].setStyle(menu_string[i].Bold);
		menu_string[i].setCharacterSize(40);
		menu_string[i].setPosition(SCREEN_SIZE.x / 2 - menu_string[i].getLocalBounds().width / 2 , 200 + i * 100);
		menu_string[i].setColor(Color::White);
	}
}
int Menu::check_selected(Vector2f point){
	int result = -1;
	for (int i = 0; i < MENU_STRING_COUNT; i++){
		if (menu_string[i].getGlobalBounds().contains(point)){
			result = i;
			break;
		}
	}
	return result;
}
void Menu::check_target(Vector2f point){ //lightintg of the menu buttons
	for (int i = 0; i < MENU_STRING_COUNT; i++){
		if (menu_string[i].getGlobalBounds().contains(point)){
			menu_string[i].setColor(Color::Red);
		}
		else{
			menu_string[i].setColor(Color::White);
		}
	}
	
}
void Menu::update(){
	sprite.setPosition(rect.left, rect.top);
}
void Menu::show(RenderWindow &window){
	window.draw(sprite);
	for (int i = 0; i < MENU_STRING_COUNT; i++){
		window.draw(menu_string[i]);
	}
}
