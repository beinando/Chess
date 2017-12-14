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
#include "field.h"




using namespace sf;
using namespace std;
using namespace parameters;

//measure performance

/*	auto start = chrono::steady_clock::now();
auto end = chrono::steady_clock::now();
double elapsed_time = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());*/


//board_status.board[old_pos_white_rook].state = 0;
//board_status.board[old_pos_black_rook].state = 0;
//board_status.board[new_pos_white_rook].state = 5;
//board_status.board[new_pos_black_rook].state = 5;
//
//
//board_status.board = board_status.update_board();


vector<int> init_board(vector<int> board) {

	for (int i = 0; i < size_board*size_board; i++) {

		board.push_back(0);

	}

	return board;

}





int main() {

	sf::RenderWindow window(sf::VideoMode(size_board *pixel_field, size_board *pixel_field), "MattseChess!");
	sf::Vector2i window_pos;
	window_pos.x = 0;
	window_pos.y = 0;
	window.setPosition(window_pos);

	vector<int> board_status;
	board_status=init_board(board_status);


	
	sf::Texture _t1;
	sf::Texture _t2;
	_t1.loadFromFile("images/whitefield.png");
	_t2.loadFromFile("images/blackfield.png");
	const int size = size_board;
	sf::Sprite board[4][4];
	//set sprites for fields
	for (int i = 0; i < size_board; i++) {
		for (int j = 0; j < size_board; j++) {

			if ((i + j) % 2 == 0) {
				board[i][j] = sf::Sprite(_t1);
			}
			else {
				board[i][j] = sf::Sprite(_t2);
			}

			board[i][j].setPosition(i * pixel_field, j * pixel_field);

		}

	}

	static int new_pos_white_rook = 0;
	static int new_pos_black_rook = 15;
	//
	figure white_rook = figure(3, 0, true);
	Sprite white_rook_sprite(white_rook.texture);
	white_rook_sprite.setPosition(0, 0);

	figure black_rook = figure(5, 15, false);
	Sprite black_rook_sprite(black_rook.texture);
	black_rook_sprite.setPosition(3*pixel_field, 3* pixel_field);

	figure white_king = figure(5, 0, true);
	Sprite white_king_sprite(white_king.texture);
	white_rook_sprite.setPosition(3 * pixel_field, 0);

	figure black_king = figure(5, 15, false);
	Sprite black_king_sprite(black_king.texture);
	black_king_sprite.setPosition(0, 3 * pixel_field);

	
	field test_field = field();
	
	

	
	while (window.isOpen())
	{
		auto start = chrono::steady_clock::now();
		sf::Event e;

		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed)
				window.close();
			break;

		}

		if (parameters::visual_output) {
			//Draw field

			
			for (int i = 0; i < size_board; i++) {
				for (int j = 0; j < size_board; j++) {
					window.draw(board[i][j]);
				}
			}
		}
		

		//int attack_number = test_field.calculate_attacked_by(test_field.index, black_rook.allowed_fields);
		sleep(time_scale);

	
	
	

		

	static int is_odd = 2;
	int old_pos_white_rook = 0;
	int old_pos_black_rook = 0;
	
	if(is_odd%2==0){

		if(white_rook.is_alive==true){
			old_pos_white_rook = new_pos_white_rook;
			new_pos_white_rook = white_rook.make_random_figure_move(white_rook.type, white_rook.position, board_status);
			//for graphics
			white_rook_sprite.setPosition(get_x_from_position(new_pos_white_rook), get_y_from_position(new_pos_white_rook));
			//for intern calculations
			white_rook.position = new_pos_white_rook;


		}
	}
	else if(is_odd%2!=0){
		if (black_rook.is_alive == true) {
			old_pos_black_rook = new_pos_black_rook;
			new_pos_black_rook = black_rook.make_random_figure_move(black_rook.type, black_rook.position, board_status);
			//for graphics
			black_rook_sprite.setPosition(get_x_from_position(new_pos_black_rook), get_y_from_position(new_pos_black_rook));
			//for intern calculations

			black_rook.position = new_pos_black_rook;
		}
	}
	
	board_status[old_pos_white_rook] = 0;
	board_status[old_pos_black_rook] = 0;
	board_status[new_pos_white_rook] = 5;
	board_status[new_pos_black_rook] = 5;


	//
	//
	//board_status.board = board_status.update_board();


	if (white_rook.is_alive) {
		window.draw(white_rook_sprite);
	}
	if (black_rook.is_alive) {
		window.draw(black_rook_sprite);
	}
	window.display();
	is_odd++;

	test_field.index = black_rook.position;
	vector<int> allowed_test = white_rook.calculate_allowed_fields(3, white_rook.position, board_status);
	int attack_by = test_field.calculate_attacked_by(test_field.index, allowed_test);
	cout << "attack_by    " << attack_by << endl;

	/*if (white_rook.position == black_rook.position) {

		black_rook.is_alive = false;
		

	}*/

	//int x = 0;
	//int y = 0;
	//vector<int> allowed_fields = rook.calculate_allowed_fields(0, 0);
	//for (int i = 0; i < allowed_fields.size(); i++){

	//x = get_x_from_position(allowed_fields[i]);
	//y = get_y_from_position(allowed_fields[i]);
	//rook_sprite.setPosition(x, y);
	
	window.clear();
	auto end = chrono::steady_clock::now();
	double elapsed_time = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
	cout << "elapsed_time    " << elapsed_time << endl;
	


	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		time_scale = time_scale/1.15;

	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		time_scale = time_scale*1.15;

	}

	CloseConnection();
	}


}

