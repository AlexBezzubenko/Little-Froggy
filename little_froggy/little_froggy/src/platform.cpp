#include "headers/platform.h"
#include "headers/consts.h"

Platform::Platform(){
}
Platform::Platform(Texture &image){		// constructor
	type = rand() % 5;  
	dx = 0;
	dy = 0;
	timer = 0;
	sprite.setTexture(image);
	rect = FloatRect(0, screen_size.y / 2, 125, 60);
	temp = rect;
	temp.top += 30;
	temp.height -= 30;
	crashed = false;
	frog_on = false;
	sprite.setTextureRect(IntRect(275, 205, 125, 60));
}

void Platform::update(float time){

	if (rect.left + rect.width < border){
		
		for (int i = 0; i < 4; i++){
			if (plats[i].rect == rect){
				
				int previous = i - 1;
				if (i == 0) {
					previous = 3;
				}
				type = rand() % 5;
				while (plats[previous].type == type){
					type = rand() % 5;
				}
				rect.left = plats[previous].rect.left + 3 * rect.width;
				if (rect.left + rect.width < border + screen_size.x){
					rect.left = border + screen_size.x;
				}
				crashed = false;
				timer = 0;
				frog_on = false;
			}
		}
		rect.top = screen_size.y / 2;
		
		dx = dy = 0;
		if (type == 2) dx = -0.03;
	}
	if (type == 0){
		sprite.setTextureRect(IntRect(275, 205, 125, 60));
		dx = 0;
		dy = 0;
	}
	if (type == 1){
		sprite.setTextureRect(IntRect(275, 205, 125, 60));
		if (rect.top < 100){
			dy = 0.03;
		}
		if (rect.top >= screen_size.y / 2){
			dy = -0.03;
		}
	}

	if (type == 2){
		sprite.setTextureRect(IntRect(275, 205, 125, 60));
		for (int i = 0; i < 4; i++){
			if (plats[i].rect == rect){
				int next = i + 1;

				if (i == 3){
					next = 0;
				};

				if (rect.left + rect.width > plats[next].rect.left - 10 
					&& abs(rect.left - plats[next].rect.left) < rect.width + 20){
					dx = -0.03;
				}
				if (rect.left + rect.width > border + screen_size.x){
					dx = -0.03;
				}

				int previous = i - 1;
				if (i == 0) {
					previous = 3;
				}

				if (rect.left < plats[previous].rect.left + plats[previous].rect.width + 10 
					&& abs(rect.left - plats[previous].rect.left) < rect.width + 20){
					dx = 0.03;
				}
				if ( rect.left < border){
					dx = 0.03;
				}
			}
		}
	}
	if (type == 3){
		dx = 0;
		dy = 0;
		
		if (!crashed){
			sprite.setTextureRect(IntRect(0, 276, 125, 60));
		}
		  
		
		if (frog_on){
			crashed = true;
			sprite.setTextureRect(IntRect(140, 210, 125, 60));
			float time1 = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time1;
			std::cout << timer << "   " << std::endl;
		}
			else
		{
				clock.restart();
		}	
		if (timer > 1 && crashed){
			rect.top += screen_size.y;
			timer = 0;
		}

	}
	if (type == 4){
		dx = 0;
		dy = 0;
		sprite.setTextureRect(IntRect(136, 275, 125, 60));
		rect.top = 0 - (rect.height - temp.height);
	}
	rect.top += dy*time;
	rect.left += dx*time;
	
	sprite.setPosition(rect.left - offset_x, rect.top - offset_y);
	temp = rect;
	temp.top += 30;
	temp.height -= 30;
}

void Platform::draw(RenderWindow &window){
	window.draw(sprite);
}