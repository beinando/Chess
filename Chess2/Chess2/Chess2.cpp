#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <vector>
#include <time.h>       /* time */
#include <random>
#include "Connector.hpp"
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Functions.hpp"
#include "figure.h"



using namespace sf;
using namespace std;
using namespace parameters;

//measure performance

/*	auto start = chrono::steady_clock::now();
auto end = chrono::steady_clock::now();
double elapsed_time = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());*/










int main() {

	sf::RenderWindow window(sf::VideoMode(size_board *pixel_field, size_board *pixel_field), "MattseChess!");

	sf::Texture _t1;
	sf::Texture _t2;
	_t1.loadFromFile("images/whitefield.png");
	_t2.loadFromFile("images/blackfield.png");

	sf::Sprite field[5][5];
	//set sprites for fields
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {

			if ((i + j) % 2 == 0) {
				field[i][j] = sf::Sprite(_t1);
			}
			else {
				field[i][j] = sf::Sprite(_t2);
			}

			field[i][j].setPosition(i * pixel_field, j * pixel_field);

		}

	}

	static int new_pos = 0;

	static figure rook = figure(3, 0, true);

	static Sprite rook_sprite(rook.texture);

	while (window.isOpen())
	{
		sf::Event e;

		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed)
				window.close();
			break;

		}

		if (parameters::visual_output) {
			//Draw field

			
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					window.draw(field[i][j]);
				}
			}
		}

	
	

	

	

	rook_sprite.setPosition(get_x_from_position(new_pos), get_y_from_position(new_pos));
	new_pos = rook.make_random_figure_move(rook);
	rook.position = new_pos;


	//int x = 0;
	//int y = 0;
	//vector<int> allowed_fields = rook.calculate_allowed_fields(0, 0);
	//for (int i = 0; i < allowed_fields.size(); i++){

	//x = get_x_from_position(allowed_fields[i]);
	//y = get_y_from_position(allowed_fields[i]);
	//rook_sprite.setPosition(x, y);
	window.draw(rook_sprite);
	
	sleep(2000);
	
	window.display();
	window.clear();
	



	CloseConnection();
	}


}

