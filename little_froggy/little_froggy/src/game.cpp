/* Little Froggy
 * Copyright(c) 2015 by Alex Bezzubenko
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt 
 */

#include "headers/game.h"
#include <iostream>
#include <sstream>
#include <fstream>

float offset_x = 0;
float offset_y = 0;
float border = 0;

Platform plats[PLATS_COUNT];

Game::Game() 
{
	game_is_running = false;
	game_over = false;

	music.openFromFile("res/music/main_sound.ogg");
	game_over_music.openFromFile("res/music/star_wars.ogg");
		 
	game_texture = new Texture();
	game_texture->loadFromFile("res/images/frog_new.png");
	
	background = new Texture();
	background->loadFromFile("res/images/background.jpg");

	sprite_map.setTexture(*background);
	sprite_map.setTextureRect(IntRect(0, 0, 2048, 1548));
	sprite_map.setScale(1, 0.5);

	frog = *game_texture;
	arrow = *game_texture;
	for (int i = 0; i < CLOUDS_COUNT; i++){
		clouds[i] = { *game_texture, i};
	}
	sun = *game_texture;
	tongue = *game_texture;
	
	fly = { *game_texture, INTRECT_PLATS_FLY };
	bee = { *game_texture, INTRECT_PLATS_BEE };

	bonus_strawberry = *game_texture;
	bonus_strawberry.set_current_position(-100, 300);
	
	bonus_elixir = *game_texture;
	bonus_elixir.set_current_position(-100, 300);

	
	fly.set_current_position(500, 400);
	bee.set_current_position(900, 500);

	for (int i = 0; i < PLATS_COUNT; i++){
		plats[i] = *game_texture;
		plats[i].set_rect_left(i * 125 + 250 * (i + 1));
	}
	
	for (int i = 0; i < FLOOR_COUNT; i++){
		floor_[i] = *game_texture;
		floor_[i].set_rect_left(i * floor_[i].get_rect().width); 
	}
	for (int i = 0; i < COIN_COUNT; i++){
		coin[i] = *game_texture;
		coin[i].set_coordinates(plats[i].get_rect().left + plats[i].get_rect().width / 2 
								- coin[i].get_rect().width / 2, coin[i].get_rect().top);
	}
	for (int i = 0; i < HEARTS_COUNT; i++){
		hearts[i] = *game_texture;
		hearts[i].set_rect_left(10 + i * (hearts[i].get_rect().width + 10));
	}

	hearts[0].set_full();
	hearts[1].set_full();
	lifes_count = 2;

	plats[0].set_type(0);
	plats[1].set_type(4);
	
	font.loadFromFile("res/ubuntu.ttf");
	game_over_text.setFont(font);
	game_over_text.setString("Game Over") ;	
	game_over_text.setCharacterSize(72); 
	game_over_text.setPosition(SCREEN_SIZE.x / 2 - game_over_text.getLocalBounds().width / 2,
							   SCREEN_SIZE.y / 2 - 200);
	game_over_text.setColor(Color::Transparent);

	reset_text.setFont(font);
	reset_text.setString("Reset");
	reset_text.setCharacterSize(50);
	reset_text.setPosition(SCREEN_SIZE.x / 2 - reset_text.getLocalBounds().width / 2,
						   SCREEN_SIZE.y / 2 - 100);
	reset_text.setColor(Color::Transparent);

	score_text.setFont(font);
	score_text.setPosition(SCREEN_SIZE.x - 300, 0);
	score_text.setCharacterSize(50);
	score_text.setColor(Color::Red);

	highscore_text.setFont(font);
	highscore_text.setPosition(SCREEN_SIZE.x - 350, 60);
	highscore_text.setCharacterSize(50);
	highscore_text.setColor(Color::White);

	new_highscore_text.setFont(font);
	new_highscore_text.setString("NEW HIGHSCORE");
	new_highscore_text.setCharacterSize(72);
	new_highscore_text.setPosition(SCREEN_SIZE.x / 2 - new_highscore_text.getLocalBounds().width / 2, 0);
	new_highscore_text.setColor(Color::Transparent);
	
	menu_texture = new Texture();
	menu_texture->loadFromFile("res/images/background_menu.jpg");
	menu = { *menu_texture, font };

	std::ifstream fin("score.txt"); 
	fin >> highscore;
	fin.close();
}

void Game::run()
{
	window.create(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "Little froggy"/*, Style::Fullscreen*/);
	/*bool fullscreen = true;
	if (fullscreen){*/
		for (int i = 0; i < FLOOR_COUNT; i++){
			floor_[i].set_rect_top(floor_[i].get_rect().top + floor_[i].get_rect().height);
		}
	//}
	window.setFramerateLimit(240);
	while (window.isOpen())
	{
		while (!game_is_running){
			menu.update();
			window.clear(Color::White);
			menu.show(window);
			window.display();
			Event event;
			while (window.pollEvent(event)){
				if (event.type == event.MouseMoved){
					Vector2i cursor_position = Mouse::getPosition(window);
					menu.check_target(Vector2f(cursor_position));
				}
				if(event.type == event.MouseButtonPressed){
					Vector2i cursor_position = Mouse::getPosition(window);
					int selected_field = menu.check_selected(Vector2f(cursor_position));
					game_is_running = true;
					
					switch (selected_field)
					{
					case 0: 
						game_mode = 1;
						break;
					case 1:
						game_mode = 2;
						break;
					case 2:
						window.close();
						break;
					default:
						game_is_running = false;
						break;
					}
					break;
				}
			}
		}
		if (game_is_running){
			if (music.getStatus() != music.Playing
			&& game_over_music.getStatus() != game_over_music.Playing){
				music.play();
			}
			float time = clock.getElapsedTime().asMicroseconds();

			clock.restart();
			time = time / game_speed;
			processEvents(time);
				
			if (!window.isOpen()){
				return;
			}
			
			object_update(time);
			render();
		}
	}
}
void Game::object_update(float time) // =border
{
	if (frog.get_rect().left > border + SCREEN_SIZE.x / 2){
		border = frog.get_rect().left - SCREEN_SIZE.x / 2;
		std::cout << "border"<< border << std::endl;
	}

	arrow.set_coordinates(frog.get_rect().left + frog.get_rect().width / 2, frog.get_rect().top + 40);
	
	if (frog.is_tongue_out() && !frog.is_on_tongue()){
		tongue.set_rect_left(frog.get_mouth().x + tongue.get_rect().height * sin(tongue.get_sprite().getRotation() * 3.1415 / 180));
		tongue.set_rect_top(frog.get_mouth().y - tongue.get_rect().height * cos(tongue.get_sprite().getRotation() * 3.1415 / 180));
	}
	for (int i = 0; i < PLATS_COUNT; i++) {
		plats[i].update(time);

		if (plats[i].get_type() == 1 && !frog.is_on_tongue()){
			if (frog.is_on_ground() && plats[i].get_help_rect().top >= frog.get_rect().top - frog.get_rect().height){
				if (frog.get_rect().left > plats[i].get_rect().left - frog.get_rect().width
					&& frog.get_rect().left < plats[i].get_rect().left + plats[i].get_rect().width) {
					frog.set_rect_top(plats[i].get_help_rect().top - frog.get_rect().height);
				}
			}
		}		
	}
	for (int i = 0; i < COIN_COUNT; i++){
		if (frog.get_rect().intersects(coin[i].get_rect())){
			coin[i].set_coordinates(coin[i].get_rect().left, SCREEN_SIZE.y);
			score += 1;
		}
	}
	if (frog.get_rect().intersects(bonus_elixir.get_rect())){
		if (lifes_count < 3){
			lifes_count++;
		}
		hearts[lifes_count - 1].set_full();
		bonus_elixir.set_current_position(border + SCREEN_SIZE.x / 2, SCREEN_SIZE.y); 
	}
	
	if (frog.get_rect().intersects(bonus_strawberry.get_rect())){
		score += 3;
		lifes_count += 3;
		if (lifes_count > 3){
			lifes_count = 3;
		}
		for (int i = 0; i < HEARTS_COUNT; i++){
			hearts[i].set_full();
		}
		bonus_strawberry.set_current_position(border + SCREEN_SIZE.x / 2, SCREEN_SIZE.y);
	}
	
	for (int i = 0; i < FLOOR_COUNT; i++){
		if (frog.get_rect().top + frog.get_rect().height > floor_[i].get_rect().top + floor_[i].get_rect().height / 3){
			if (lifes_count > 0){
				hearts[lifes_count - 1].set_empty();
				lifes_count--;
			}

			if (lifes_count == 0){
				if (music.getStatus() == music.Playing) music.stop();
				if (game_over_music.getStatus() != game_over_music.Playing) game_over_music.play();
				GameOver();
				break;
			}
			else {
				frog.respawn();
			}
		}
	}
	if (frog.get_rect().intersects(bee.get_rect())){
		if (lifes_count > 0){
			hearts[lifes_count - 1].set_empty();
			lifes_count--;
		}
		if (!frog.is_on_tongue() && !frog.is_on_ground()){
			if (frog.get_rect().left < bee.get_rect().left){
				frog.set_acceleration_x(-0.2);
			}
			if (frog.get_rect().left > bee.get_rect().left){
				frog.set_acceleration_x(0.2);
			}
			if (frog.get_rect().top < bee.get_rect().top){
				frog.set_rect_top(bee.get_rect().top - frog.get_rect().height);
				frog.set_acceleration_y(-0.2);
			}
			if (frog.get_rect().top > bee.get_rect().top){
				frog.set_rect_top(bee.get_rect().top + bee.get_rect().height);
				frog.set_acceleration_y(0.2);
			}
		}
		bee.stop();
		if (lifes_count == 0){
			if (music.getStatus() == music.Playing) music.stop();
			if (game_over_music.getStatus() != game_over_music.Playing) game_over_music.play();
			GameOver();
		}
	}

	tongue.update();
	frog.Collision(1);
	frog.update(time);
	arrow.update();
	fly.update(time);
	bee.update(time);
	bonus_strawberry.update();
	bonus_elixir.update();
	for (int i = 0; i < CLOUDS_COUNT; i++){
		clouds[i].update(time);
	}
	sun.update(time);
	
	for (int i = 0; i < FLOOR_COUNT; i++){
		floor_[i].update();
	}
	for (int i = 0; i < COIN_COUNT; i++){
		coin[i].update();
	}
	for (int i = 0; i < HEARTS_COUNT; i++){
		hearts[i].update();
	}
	std::stringstream score_str;    
	score_str << score;
	score_text.setString("Score: " + score_str.str());
	std::stringstream highscore_str;
	highscore_str << highscore;
	highscore_text.setString("Highscore: " + highscore_str.str());
}

void Game::processEvents(float time)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			return;
		}
	}
	if (game_mode == 2 && !game_over && !frog.is_on_tongue()){
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)){
			if (frog.get_acceleration_x() > -0.3 && !frog.is_on_ground()){
				frog.change_acceleration_x(-0.002);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
			if (frog.get_acceleration_x() < 0.3 && !frog.is_on_ground()){
				frog.change_acceleration_x(0.002);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) || (Keyboard::isKeyPressed(Keyboard::Up))) {
			if (frog.is_on_ground()) {
				frog.set_rect_top(frog.get_rect().top - 20);
				frog.set_acceleration_y(-0.5);
				frog.set_on_ground(false);
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && !frog.is_on_ground() && !game_over) {
		frog.set_acceleration_y(0.3);
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)){
		music.stop();
		window.close();
	}
	
	if (Mouse::isButtonPressed(Mouse::Right) && !game_over){
		tongue.set_dot(Mouse::getPosition(window));
		
		for (int i = 0; i < PLATS_COUNT; i++) {
			double distance_x, distance_y;
		
			distance_x = frog.get_mouth().x - (tongue.get_dot().x + offset_x + tongue.get_rect().width / 2);
			distance_y = plats[i].get_rect().top + plats[i].get_rect().height - frog.get_mouth().y;
			double distance = sqrt(pow(abs(distance_y), 2) + pow(abs(distance_x), 2));

			if (plats[i].get_rect().left - offset_x < tongue.get_dot().x
				&& tongue.get_dot().x < (plats[i].get_rect().left + plats[i].get_rect().width - offset_x)
				&& tongue.get_dot().y < frog.get_rect().top + frog.get_rect().height
				&& plats[i].get_type() == 4
				&& !frog.is_on_tongue()
				&& distance < SCREEN_SIZE.y / 2 + 150
				){
				tongue.set_rect_left(tongue.get_dot().x + offset_x);						// set the tongue's high point
				tongue.set_rect_top(plats[i].get_rect().top + plats[i].get_rect().height - 5);
				/// set the direction
				if (frog.get_rect().left > plats[i].get_rect().left + plats[i].get_rect().width / 2){
					delta_angle = abs(delta_angle);
				}
				if (frog.get_rect().left + frog.get_rect().width < plats[i].get_rect().left + plats[i].get_rect().width / 2) {
					delta_angle = -1 * abs(delta_angle);
				}
				

				if (distance_y < 0) {
					tongue.set_sprite_scale(1.f, distance / tongue.get_original_height());
				}
				tongue.set_rect_height(tongue.get_original_height() * tongue.get_sprite().getScale().y);

				double  angle;
				angle = 180 / 3.1415 * atan2(abs(distance_x), abs(distance_y));

				left_angle_border = angle;
				right_angle_border = 360 - angle;

				if (distance_y <= 0 && distance_x < 0) {
					right_angle_border += 10;
				}
				if (distance_y <= 0 && distance_x > 0){
					angle *= -1;
					left_angle_border -= 10;
				}
				if (distance_y < 0){
					frog.set_on_tongue(true);
					frog.set_on_ground(true);
					frog.set_acceleration_x(0);
					frog.set_acceleration_y(0);
				}
				tongue.set_rotation(angle);
			}
			
			if (frog.is_on_tongue()){
				current_angle = tongue.get_sprite().getRotation();
				if (current_angle > left_angle_border && current_angle < 90){ // define is in III part
					delta_angle *= -1;

					if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)){
						left_angle_border += 20;
						right_angle_border -= 10;
					}
					else{
						right_angle_border += 10;
					}
					if (right_angle_border > 360){
						right_angle_border = 360;
					}
					if (right_angle_border <= 270){
						right_angle_border = 275;
					}
				}
				if (current_angle < right_angle_border && current_angle > 270){ // define IV part
					delta_angle *= -1;

					if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)){
						left_angle_border += 10;
						right_angle_border -= 20;
					}

					else{
						left_angle_border -= 10;
					}
					if (left_angle_border < 0){
						left_angle_border = 0;
					}
					if (left_angle_border >= 90){
						left_angle_border = 85;
					}

				}

				if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)){
					if (frog.get_rect().top > plats[i].get_rect().top + plats[i].get_rect().height){
						tongue.set_sprite_scale(1.f, tongue.get_sprite().getScale().y - 0.005);
						tongue.set_rect_height(tongue.get_original_height() * tongue.get_sprite().getScale().y);
					}
				}
					if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)){
						if (tongue.get_rect().height < SCREEN_SIZE.y / 2 + 150){
							tongue.set_sprite_scale(1.f, tongue.get_sprite().getScale().y + 0.005);
							tongue.set_rect_height(tongue.get_original_height() * tongue.get_sprite().getScale().y);
						}
					}

					tongue.set_rotation(current_angle + delta_angle);
					current_angle = tongue.get_sprite().getRotation();
					
					frog.set_rect_top(tongue.get_rect().top + tongue.get_rect().height *
						cos(3.1415 / 180 * current_angle) - 50); //mouth level
			
					 
					frog.set_rect_left(tongue.get_rect().left - tongue.get_rect().height
						* sin(3.1415 / 180 * current_angle) - frog.get_rect().width / 2);
					
					if (frog.get_rect().left > border + SCREEN_SIZE.x / 2){
						offset_x = frog.get_rect().left - SCREEN_SIZE.x / 2;
					}
					if (frog.get_rect().top < 20){
						offset_y = frog.get_rect().top - 20;
					} 
				}
		}
	}

	if (event.type == event.MouseButtonPressed){
		if (event.mouseButton.button == Mouse::Left){
			if (game_mode == 1){
				frog.set_point_1(Mouse::getPosition(window));
			}
			if (game_over){
				Vector2i cursor_position = Mouse::getPosition(window);
				if (reset_text.getGlobalBounds().contains(Vector2f(cursor_position))){
					offset_y = 0;
					score = 0;

					game_over = false; 
					frog.respawn();
					bee.set_current_position(border + SCREEN_SIZE.x, 300);
					lifes_count++;
					hearts[0].set_full();
					reset_text.setColor(Color::Transparent);
					game_over_text.setColor(Color::Transparent);
					new_highscore_text.setColor(Color::Transparent);
					game_over_music.stop();
					music.play();
				}
			}
		}
		if (event.mouseButton.button == Mouse::Right && !game_over){
			tongue.set_dot(Mouse::getPosition(window));
			
			int k = 0;
			for (int i = 0; i < PLATS_COUNT; i++) {
				if (!(plats[i].get_rect().left - offset_x < tongue.get_dot().x
					&& tongue.get_dot().x < (plats[i].get_rect().left + plats[i].get_rect().width - offset_x)
					&& plats[i].get_type() == 4 
					&& frog.is_on_tongue()
					)){
					k++;
					break;
				}
			}
			
			if(k > 0){
					tongue.set_dot(Mouse::getPosition());
					tongue.set_rect_left(tongue.get_dot().x + offset_x);
					tongue.set_rect_top(tongue.get_dot().y + offset_y);

					double distance_x, distance_y;
					distance_x = frog.get_mouth().x - (tongue.get_rect().left + tongue.get_rect().width / 2);
					distance_y = tongue.get_rect().top - frog.get_mouth().y;
					double distance = sqrt(pow(abs(distance_y), 2) + pow(abs(distance_x), 2));

					if (distance > SCREEN_SIZE.y / 2){
						distance = SCREEN_SIZE.y / 2;
					}
					else {
						if (fly.check_is_inrect(tongue.get_dot())){
							fly.stop();
							if (lifes_count < 3){
								lifes_count++;
							}
							hearts[lifes_count - 1].set_full();
							score += 5;
						}
					}
					tongue.set_sprite_scale(1.f, distance / tongue.get_original_height());
					tongue.set_rect_height(tongue.get_original_height() * tongue.get_sprite().getScale().y);

						double  angle;
						angle = 180 / 3.1415 * atan2(distance_x, distance_y);
						tongue.set_rotation(angle + 180);

						frog.set_on_tongue(false);
						frog.set_tongue_out(true);
			}
		}
	}

	if (event.type == event.MouseMoved){
		if (game_mode == 1){
			frog.set_point_2(Mouse::getPosition(window));

			if (frog.get_rect().left - offset_x < frog.get_point_1().x
				&& frog.get_point_1().x < frog.get_rect().left + frog.get_rect().width - offset_x
				&& frog.get_rect().top - offset_y < frog.get_point_1().y
				&& frog.get_point_1().y < frog.get_rect().top + frog.get_rect().height - offset_y){

				Vector2i point;
				point.x = frog.get_rect().left + frog.get_rect().width / 2 - offset_x;
				point.y = frog.get_rect().top + frog.get_rect().height / 2 - offset_y;
				frog.set_point_1(point);

				float scale_x, scale_y;
				scale_x = 0.8;
				scale_y = sqrt(pow((frog.get_point_1().y - frog.get_point_2().y), 2) 
						  + pow((frog.get_point_1().x - frog.get_point_2().x), 2)) / arrow.get_height();
				arrow.set_scale(scale_x, scale_y);
				rect.width *= scale_x;
				
				int distance_x, distance_y;
				distance_x = frog.get_point_1().x - frog.get_point_2().x;
				distance_y = frog.get_point_1().y - frog.get_point_2().y;

				double angle;
				if (distance_x != 0){
					angle = 180 / 3.1415 * atan2(abs(distance_y), abs(distance_x));
					if (distance_y > 0){ arrow.set_scale(0.001f, 0.001f); }
					if (distance_y <= 0 && distance_x > 0) { angle = -angle - 90; }
					if (distance_y <= 0 && distance_x < 0){ angle = angle - 270; }
				}
				else { angle = 180; };
				arrow.set_rotation(angle);
			}
		}
		if (game_over){
				Vector2i cursor_position = Mouse::getPosition(window);
				if (reset_text.getGlobalBounds().contains(Vector2f(cursor_position))){
					reset_text.setColor(Color::Red);
				}
				else{
					reset_text.setColor(Color::White);
				}
		}
	}

	if (event.type == event.MouseButtonReleased){
		if (event.mouseButton.button == Mouse::Left && game_mode == 1){
			if (frog.get_rect().left - offset_x < frog.get_point_1().x && frog.get_point_1().x < frog.get_rect().left - offset_x + 80
				&& frog.get_rect().top - offset_y < frog.get_point_1().y && frog.get_point_1().y < frog.get_rect().top - offset_y + 80){
				double acceleration_x;
				double acceleration_y;
				acceleration_x = (frog.get_point_1().x - frog.get_point_2().x) * 0.0018;
				acceleration_y = (frog.get_point_1().y - frog.get_point_2().y) * 0.0018;

				if (abs(acceleration_x) > 0.5){
					if (acceleration_x > 0) { acceleration_x = 0.5; }
					if (acceleration_x < 0) { acceleration_x = -0.5; }
				}
				if (abs(acceleration_y) > 0.5){
					if (acceleration_y > 0) { acceleration_y = 0.5; }
					if (acceleration_y < 0) { acceleration_y = -0.5; }
				}
				if (frog.is_on_ground()){
					frog.set_acceleration_y(acceleration_y);
					frog.set_acceleration_x(acceleration_x);
					frog.set_on_ground(false);
					Mouse::setPosition(frog.get_point_2(), window);
					frog.set_rect_top(frog.get_rect().top - 20);
				}
				Vector2i zero_point(0, 0);
				frog.set_point_1(zero_point);
				frog.set_point_2(zero_point);
			}
			arrow.set_scale(0.001f, 0.001f);
		}

		if (event.mouseButton.button == Mouse::Right){
			tongue.set_sprite_scale(0.001f, 0.001f);
			tongue.set_rect_height(tongue.get_original_height() * tongue.get_sprite().getScale().y);

			std::cout << "curr = "<<current_angle << "delta = "<<delta_angle<< std::endl;

			if (frog.is_on_tongue()){
				float acceleration_x = 0.2;
				float acceleration_y = 0.5;
				if (delta_angle > 0){
					acceleration_x *= -1;
				}
				float delta_angle_acceleration;
				if (current_angle > 90){
					delta_angle_acceleration = 360 - current_angle;
				}
				else{
					delta_angle_acceleration = current_angle;
				}
				acceleration_y = acceleration_y / 90 * delta_angle_acceleration;
				if (delta_angle_acceleration <= 45){
					acceleration_x = acceleration_x / 45 * delta_angle_acceleration;
				}
				else{
					acceleration_x = acceleration_x / 45 * (90 - delta_angle_acceleration);
				}
				frog.set_acceleration_x(acceleration_x);
				frog.set_acceleration_y(-acceleration_y);
				frog.set_on_tongue(false);
			}
			
			frog.set_on_ground(false);
			frog.set_tongue_out(false);
			delta_angle = -0.08;
		}
	}
}

void Game::render(){ 
	// =offset
	if (frog.get_rect().left > border + SCREEN_SIZE.x / 2){
		offset_x = frog.get_rect().left - SCREEN_SIZE.x / 2;
	}
	if (frog.get_rect().top < 20){
		offset_y = frog.get_rect().top - 20;
	}

	window.clear();
	window.draw(sprite_map);
	sun.draw(window);
	for (int i = 0; i < CLOUDS_COUNT; i++){
		clouds[i].draw(window);
	}
	for (int i = 0; i < PLATS_COUNT; i++){
		plats[i].draw(window);
	}
	arrow.draw(window);
	frog.draw(window);
	tongue.draw(window);
	bonus_strawberry.draw(window);
	bonus_elixir.draw(window);
	for (int i = 0; i < COIN_COUNT; i++){
		coin[i].draw(window);
	}
	fly.draw(window);
	bee.draw(window);
	
	for (int i = 0; i < FLOOR_COUNT; i++){
		floor_[i].draw(window);
	}
	for (int i = 0; i < HEARTS_COUNT; i++){
		hearts[i].draw(window);
	}
	
	window.draw(score_text);
	window.draw(highscore_text);
	window.draw(game_over_text);
	window.draw(new_highscore_text);
	window.draw(reset_text);
	window.display();
}

void Game::GameOver(){
	if (!game_over) {
		game_over = true;
		game_over_text.setColor(Color::Red);
		reset_text.setColor(Color::White);
	}
	frog.kill();
	
	if (highscore < score){
		new_highscore_text.setColor(Color::Blue);
		highscore = score;
		std::ofstream fout;
		fout.open("score.txt");
		fout << highscore;
		fout.close();
	}

}