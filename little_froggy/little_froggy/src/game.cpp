#include "headers/game.h"
#include <iostream>
#include <sstream>

float offset_x = 0;
float offset_y = 0;
float border = 0;
int score = 0;

Platform plats[plats_count];

Game::Game() 
{
	game_is_running = false;
	game_over = false;

	music.openFromFile("res/music/main_sound.oggv");
	game_over_music.openFromFile("res/music/star_wars.ogvg");
		 
	game_texture = new Texture();
	game_texture->loadFromFile("res/images/frog_new.png");
	
	background = new Texture();
	background->loadFromFile("res/images/background.jpg");

	sprite_map.setTexture(*background);
	sprite_map.setTextureRect(IntRect(0, 0, 2048, 1548));
	sprite_map.setScale(1, 0.5);

	frog = *game_texture;
	arrow = *game_texture;
	for (int i = 0; i < clouds_count; i++){
		clouds[i] = { *game_texture, i};
	}
	sun = *game_texture;
	tongue = *game_texture;
	
	fly = { *game_texture, intrect_plats_fly };
	bee = { *game_texture, intrect_plats_bee };

	bonus_strawberry = *game_texture;
	bonus_strawberry.set_current_position(-100, 300);
	
	bonus_elixir = *game_texture;
	bonus_elixir.set_current_position(-100, 300);

	
	fly.set_current_position(500, 400);
	bee.set_current_position(900, 500);

	for (int i = 0; i < plats_count; i++){
		plats[i] = *game_texture;
		plats[i].rect.left = i * 125 + 250 * (i + 1);
	}
	
	for (int i = 0; i < floor_count; i++){
		floor_[i] = *game_texture;
		floor_[i].rect.left = i * floor_[i].rect.width;
	}
	for (int i = 0; i < coin_count; i++){
		coin[i] = *game_texture;
		coin[i].rect.left = plats[i].rect.left + plats[i].rect.width / 2 - coin[i].rect.width / 2;
	}
	for (int i = 0; i < hearts_count; i++){
		hearts[i] = *game_texture;
		hearts[i].rect.left = 10 + i * (hearts[i].rect.width + 10);
	}

	hearts[0].set_full();
	hearts[1].set_full();
	lifes_count = 2;

	plats[0].type = 0;
	plats[1].type = 4;
	
	font.loadFromFile("res/ubuntu.ttf");
	game_over_text.setFont(font);
	game_over_text.setString("Game Over") ;	
	game_over_text.setCharacterSize(72); 
	game_over_text.setPosition(screen_size.x / 2 - game_over_text.getLocalBounds().width / 2,
							   screen_size.y / 2 - 200);
	game_over_text.setColor(Color::Transparent);

	reset_text.setFont(font);
	reset_text.setString("Reset");
	reset_text.setCharacterSize(50);
	reset_text.setPosition(screen_size.x / 2 - reset_text.getLocalBounds().width / 2,
						   screen_size.y / 2 - 100);
	reset_text.setColor(Color::Transparent);

	score_text.setFont(font);
	score_text.setPosition(screen_size.x - 300, 0);
	score_text.setCharacterSize(50);
	score_text.setColor(Color::Red);
	
	menu_texture = new Texture();
	menu_texture->loadFromFile("res/images/background_menu.jpg");
	menu = { *menu_texture, font };
}

void Game::run()
{
	window.create(VideoMode(screen_size.x, screen_size.y), "Little froggy"
	//	, Style::Fullscreen
		);
	bool fullscreen = false;
	if (fullscreen){
		for (int i = 0; i < floor_count; i++){
			floor_[i].rect.top += floor_[i].rect.height;
		}
	}
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
				
			if (!window.isOpen()){ //after prosseEv win.close and cycle is continue that's why use handy break;
				return;
			}
			
			object_update(time);
			render();
		}
	}
}
void Game::object_update(float time) // =border
{
	if (frog.rect.left > border + screen_size.x / 2){
		border = frog.rect.left - screen_size.x / 2;
		std::cout << border << std::endl;
	}

	arrow.rect.left = frog.rect.left + frog.rect.width / 2;
	arrow.rect.top = frog.rect.top + 40;
	if (frog.tongue_out && !frog.on_tongue){
		tongue.rect.left = frog.mouth.x + tongue.rect.height * sin(tongue.sprite.getRotation()*3.1415/180);
		tongue.rect.top = frog.mouth.y - tongue.rect.height * cos(tongue.sprite.getRotation()*3.1415 / 180);
	}
	for (int i = 0; i < plats_count; i++) {
		plats[i].update(time);

		if (plats[i].type == 1 && !frog.on_tongue){
			if (frog.onground && plats[i].temp.top >= frog.rect.top - frog.rect.height){
				if (frog.rect.left > plats[i].rect.left - frog.rect.width
					&& frog.rect.left < plats[i].rect.left + plats[i].rect.width) {
					frog.rect.top = plats[i].temp.top - frog.rect.height;
				}
			}
		}		
	}
	for (int i = 0; i < coin_count; i++){
		if (frog.rect.intersects(coin[i].rect)){
			coin[i].rect.top = screen_size.y;
			score += 1;
		}
	}
	if (frog.rect.intersects(bonus_elixir.rect)){
		if (lifes_count < 3){
			lifes_count++;
		}
		hearts[lifes_count - 1].set_full();
		bonus_elixir.rect.top = screen_size.y;
	}
	
	if (frog.rect.intersects(bonus_strawberry.rect)){
		lifes_count += 3;
		if (lifes_count > 3){
			lifes_count = 3;
		}
		for (int i = 0; i < hearts_count; i++){
			hearts[i].set_full();
		}
		bonus_strawberry.rect.top = screen_size.y;
	}
	
	for (int i = 0; i < floor_count; i++){
		if (frog.rect.top + frog.rect.height > floor_[i].rect.top + floor_[i].rect.height / 3){
			if (lifes_count > 0){
				hearts[lifes_count - 1].set_empty();
				lifes_count--;
			}

			if (lifes_count == 0){
				//frog.set_acceleration_y(-0.2);
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
	if (frog.rect.intersects(bee.rect)){
		if (lifes_count > 0){
			hearts[lifes_count - 1].set_empty();
			lifes_count--;
		}
		if (frog.rect.left < bee.rect.left){
			frog.set_acceleration_x(-0.2);
		}
		if (frog.rect.left > bee.rect.left){
			frog.set_acceleration_x(0.2);
		}
		if (frog.rect.top < bee.rect.top){
			frog.rect.top = bee.rect.top - frog.rect.height;
			frog.set_acceleration_y(-0.2);
		}
		if (frog.rect.top > bee.rect.top){
			frog.rect.top = bee.rect.top + bee.rect.height;
			frog.set_acceleration_y(0.2);
		}
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
	for (int i = 0; i < clouds_count; i++){
		clouds[i].update(time);
	}
	sun.update(time);
	
	for (int i = 0; i < floor_count; i++){
		floor_[i].update();
	}
	for (int i = 0; i < coin_count; i++){
		coin[i].update();
	}
	for (int i = 0; i < hearts_count; i++){
		hearts[i].update();
	}
	std::stringstream score_str;    
	score_str << score;
	score_text.setString("Score: " + score_str.str());
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
	if (game_mode == 2){
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)){
			if (frog.get_acceleration_x() > -0.3 && !frog.onground){
				frog.change_acceleration_x(-0.002);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
			if (frog.get_acceleration_x() < 0.3 && !frog.onground){
				frog.change_acceleration_x(0.002);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) || (Keyboard::isKeyPressed(Keyboard::Up))) {
			if (frog.onground) {
				frog.rect.top -= 20;
				frog.set_acceleration_y(-0.5);
				frog.onground = false;
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && !frog.onground) {
		frog.set_acceleration_y(0.3);
	}

	if (Keyboard::isKeyPressed(Keyboard::R)){
		offset_y = 0;
		frog.alive = true;
		frog.rect.left = border + 250;
		frog.rect.top = 50;
		frog.set_acceleration_x(0);
		frog.set_acceleration_y(0);
		game_over_text.setColor(Color::Transparent);
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)){
		music.stop();
		window.close();
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && !frog.on_tongue){
		frog.rect.top -= 20;
		frog.set_acceleration_y(-0.2);
	}
	
	
	
	if (Mouse::isButtonPressed(Mouse::Right)){
		tongue.dot = Mouse::getPosition(window);

		for (int i = 0; i < plats_count; i++) {
			double distance_x, distance_y;
		
			distance_x = frog.mouth.x - (tongue.dot.x + offset_x + tongue.rect.width / 2);
			distance_y = plats[i].rect.top + plats[i].rect.height - frog.mouth.y;
			double distance = sqrt(pow(abs(distance_y), 2) + pow(abs(distance_x), 2));

			if (plats[i].rect.left - offset_x < tongue.dot.x
				&& tongue.dot.x < (plats[i].rect.left + plats[i].rect.width - offset_x)
				&& tongue.dot.y < frog.rect.top + frog.rect.height
				&& plats[i].type == 4
				&& !frog.on_tongue
				&& distance < screen_size.y / 2 + 150
				//&& !frog.tongue_out
				){
				tongue.rect.left = tongue.dot.x + offset_x;						// set the tongue's high point
				tongue.rect.top = plats[i].rect.top + plats[i].rect.height - 5;
				/// set the direction
				if (frog.rect.left > plats[i].rect.left + plats[i].rect.width / 2){
					delta_angle = abs(delta_angle);
				}
				if (frog.rect.left + frog.rect.width < plats[i].rect.left + plats[i].rect.width / 2) {
					delta_angle = -1 * abs(delta_angle);
				}
				

				if (distance_y < 0) {
					tongue.sprite.setScale(1.f, distance / tongue.original_height);
				}
				tongue.rect.height = tongue.original_height * tongue.sprite.getScale().y;

				double  angle;
				angle = 180 / 3.1415 * atan2(abs(distance_x), abs(distance_y));

				left_angle_border = angle;
				right_angle_border = 360 - angle;

				if (distance_y <= 0 && distance_x < 0) {
					//angle = 90 - angle; 
					right_angle_border += 10;
				}
				if (distance_y <= 0 && distance_x > 0){
					angle *= -1; //-(90 - angle); 
					left_angle_border -= 10;
				}
				if (distance_y < 0){
					frog.on_tongue = true;
					frog.onground = true;
					frog.set_acceleration_x(0);
					frog.set_acceleration_y(0);
				}
				tongue.sprite.setRotation(angle);
			}
			
			if (frog.on_tongue){
				float current_angle = tongue.sprite.getRotation();
				//std::cout << current_angle << std::endl;
				if (current_angle > left_angle_border && current_angle < 90){ // define III part
					delta_angle *= -1;

					std::cout << "  right = " << right_angle_border << std::endl;

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

					std::cout << "left = " << left_angle_border << std::endl;

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
					if(frog.rect.top > plats[i].rect.top + plats[i].rect.height){
						tongue.sprite.setScale(1.f, tongue.sprite.getScale().y - 0.005);
						tongue.rect.height = tongue.original_height * tongue.sprite.getScale().y;
					}
				}
					if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)){
						if (tongue.rect.height < screen_size.y / 2 + 150){
							tongue.sprite.setScale(1.f, tongue.sprite.getScale().y + 0.005);
							tongue.rect.height = tongue.original_height * tongue.sprite.getScale().y;
						}
					}

					tongue.sprite.setRotation(current_angle + delta_angle);
					current_angle = tongue.sprite.getRotation();
					
					frog.rect.top = tongue.rect.top + tongue.rect.height *
						cos(3.1415 / 180 * current_angle) - 50; //mouth level
			
					 
					frog.rect.left = tongue.rect.left - tongue.rect.height
						* sin(3.1415 / 180 * current_angle) - frog.rect.width / 2;
					
					if (frog.rect.left > border + screen_size.x / 2){
						offset_x = frog.rect.left - screen_size.x / 2;
					}
					if (frog.rect.top < 20){
						offset_y = frog.rect.top - 20;
					} 
				}
		}
	}

	if (event.type == event.MouseButtonPressed){
		if (event.mouseButton.button == Mouse::Left){
			if (game_mode == 1){
				frog.point_1 = Mouse::getPosition(window);
			}
			if (game_over){
				Vector2i cursor_position = Mouse::getPosition(window);
				if (reset_text.getGlobalBounds().contains(Vector2f(cursor_position))){
					offset_y = 0;
					score = 0;

					game_over = false; 
					frog.respawn();
					lifes_count++;
					hearts[0].set_full();
					reset_text.setColor(Color::Transparent);
					game_over_text.setColor(Color::Transparent);
				}
			}
		}
		if (event.mouseButton.button == Mouse::Right){
			tongue.dot = Mouse::getPosition(window);
			int k = 0;
			for (int i = 0; i < plats_count; i++) {
				if (!(plats[i].rect.left - offset_x < tongue.dot.x
					&& tongue.dot.x < (plats[i].rect.left + plats[i].rect.width - offset_x)
					&& plats[i].type == 4 
					&& frog.on_tongue
					)){
					k++;
					break;
				}
			}
			
			if(k > 0){
				    tongue.dot = Mouse::getPosition();
					tongue.rect.left = tongue.dot.x + offset_x;
					tongue.rect.top = tongue.dot.y + offset_y;

					double distance_x, distance_y;
					distance_x = frog.mouth.x - (tongue.rect.left + tongue.rect.width / 2);
					distance_y = tongue.rect.top - frog.mouth.y;
					double distance = sqrt(pow(abs(distance_y), 2) + pow(abs(distance_x), 2));

					if (distance > screen_size.y / 2){
						distance = screen_size.y / 2;
					}
						tongue.sprite.setScale(1.f, distance / tongue.original_height);
						tongue.rect.height = tongue.original_height * tongue.sprite.getScale().y;

						double  angle;
						angle = 180 / 3.1415 * atan2(distance_x, distance_y);
						tongue.sprite.setRotation(angle + 180);

						frog.on_tongue = false;
						frog.tongue_out = true;
					
						if (fly.check_is_inrect(tongue.dot)){
							fly.stop();
							if (lifes_count < 3){
								lifes_count++;
							}
							hearts[lifes_count - 1].set_full();
						}
			}
		}
	}
///////////////////////////////////////////////////////////////////////////////
	if (event.type == event.MouseMoved){
		if (game_mode == 1){
			frog.point_2 = Mouse::getPosition(window);

			if (frog.rect.left - offset_x < frog.point_1.x
				&& frog.point_1.x < frog.rect.left + frog.rect.width - offset_x
				&& frog.rect.top - offset_y < frog.point_1.y
				&& frog.point_1.y < frog.rect.top + frog.rect.height - offset_y){

				frog.point_1.x = frog.rect.left + frog.rect.width / 2 - offset_x;
				frog.point_1.y = frog.rect.top + frog.rect.height / 2 - offset_y;

				float scale_x, scale_y;
				scale_x = 0.8;
				scale_y = sqrt(pow((frog.point_1.y - frog.point_2.y), 2) + pow((frog.point_1.x - frog.point_2.x), 2)) / arrow.rect.height;
				arrow.sprite.setScale(scale_x, scale_y);
				rect.width *= scale_x;
				arrow.sprite.setOrigin(arrow.rect.width / 2, 0);
				int distance_x, distance_y;
				distance_x = frog.point_1.x - frog.point_2.x;
				distance_y = frog.point_1.y - frog.point_2.y;

				double angle;
				if (distance_x != 0){
					angle = 180 / 3.1415 * atan2(abs(distance_y), abs(distance_x));
					if (distance_y > 0){ arrow.sprite.setScale(0.001f, 0.001f); }
					if (distance_y <= 0 && distance_x > 0) { angle = -angle - 90; }
					if (distance_y <= 0 && distance_x < 0){ angle = angle - 270; }
				}
				else { angle = 180; };
				arrow.sprite.setRotation(angle);
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
			if (frog.rect.left - offset_x < frog.point_1.x && frog.point_1.x < frog.rect.left - offset_x + 80
				&& frog.rect.top - offset_y < frog.point_1.y && frog.point_1.y < frog.rect.top - offset_y + 80){
				double acceleration_x;
				double acceleration_y;
				acceleration_x = (frog.point_1.x - frog.point_2.x) * 0.0018;
				acceleration_y = (frog.point_1.y - frog.point_2.y) * 0.0018;

				if (abs(acceleration_x) > 0.5){
					if (acceleration_x > 0) { acceleration_x = 0.5; }
					if (acceleration_x < 0) { acceleration_x = -0.5; }
				}
				if (abs(acceleration_y) > 0.5){
					if (acceleration_y > 0) { acceleration_y = 0.5; }
					if (acceleration_y < 0) { acceleration_y = -0.5; }
				}
				if (frog.onground){
					frog.set_acceleration_y(acceleration_y);
					frog.set_acceleration_x(acceleration_x);
					frog.onground = false;
					Mouse::setPosition(frog.point_2, window);
					frog.rect.top -= 20;
				}
				frog.point_1.x = frog.point_1.y = frog.point_2.x = frog.point_2.y = 0;
			}
			arrow.sprite.setScale(0.001f, 0.001f);
		}

		if (event.mouseButton.button == Mouse::Right){
			tongue.sprite.setScale(0.001f, 0.001f);
			tongue.rect.height = tongue.original_height * tongue.sprite.getScale().y;

			if (frog.on_tongue){
				//frog.set_acceleration_x(0.2); 
				//frog.set_acceleration_y(-0.2);
				frog.on_tongue = false;
			}
			
			frog.onground = false;
			frog.tongue_out = false;
			delta_angle = -0.08;
		}
	}
}

void Game::render(){ // =offset
	if (frog.rect.left > border + screen_size.x / 2){
		offset_x = frog.rect.left - screen_size.x / 2;
	}
	if (frog.rect.top < 20){
		offset_y = frog.rect.top - 20;
	}

	window.clear();
	window.draw(sprite_map);
	sun.draw(window);
	for (int i = 0; i < clouds_count; i++){
		clouds[i].draw(window);
	}
	arrow.draw(window);
	frog.draw(window);
	tongue.draw(window);
	fly.draw(window);
	bee.draw(window);
	bonus_strawberry.draw(window);
	bonus_elixir.draw(window);

	for (int i = 0; i < plats_count; i++){
		plats[i].draw(window);
	}
	for (int i = 0; i < floor_count; i++){
		floor_[i].draw(window);
	}
	for (int i = 0; i < hearts_count; i++){
		hearts[i].draw(window);
	}
	for (int i = 0; i < coin_count; i++){
		coin[i].draw(window);
	}
	window.draw(score_text);
	window.draw(game_over_text);
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
}