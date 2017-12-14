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
	int win = 0;
	int lose = 0;

	//dummy key getting into the next loop
	int loop_key;
	//dummy key getting into the next step
	int step_key;
	

	//BIG loop over almost everything in  main()
	for(int i=0; i<loops;i++){

	int start_vector_size=size_board*size_board;
	vector<int> double_indices;
	vector<double> start_vector;

	for (int i = 0; i < start_vector_size; i++) {
		start_vector.push_back(0);
	}

	//Rewrite values file with zeroes
	if(reset_values){
		functions::zeroes_in_file(start_vector);
	}
	vector<double> values;
	vector<double> new_values;
	vector<int> previous_positions;

	values = functions::read_from_file(start_vector);

	new_values = values;

	functions::write_in_file(new_values);
	

	sf::RenderWindow window(sf::VideoMode(size_board *pixel_field, size_board *pixel_field), "MattseChess!");
	



	sf::Texture _t1;
	sf::Texture _t2;
	sf::Texture _goal;
	sf::Texture _fire;
	sf::Texture _fire2;
	sf::Texture _smiley;
	sf::Texture _suspicious;
	sf::Texture _suspicious2;
	sf::Texture _wink;

	_fire.loadFromFile("images/fire.png");
	_fire2.loadFromFile("images/fire.png");
	_goal.loadFromFile("images/racing.png");
	_smiley.loadFromFile("images/thinking.png");
	_suspicious.loadFromFile("images/suspicious.png");
	_suspicious2.loadFromFile("images/suspicious.png");
	_wink.loadFromFile("images/wink.png");
	_t1.loadFromFile("images/whitefield.png");
	_t2.loadFromFile("images/blackfield.png");
	
	

	sf::Sprite fire(_fire);
	sf::Sprite fire2(_fire2);
	sf::Sprite smiley(_smiley);
	sf::Sprite goal(_goal);
	sf::Sprite suspicious(_suspicious);
	sf::Sprite suspicious2(_suspicious2);
	sf::Sprite wink(_wink);

	suspicious.setPosition(2* pixel_field, 2 * pixel_field);
	suspicious2.setPosition(0 * pixel_field, 4 * pixel_field);
	fire.setPosition(2 * pixel_field, 2 * pixel_field);
	fire2.setPosition(0 * pixel_field, 4 * pixel_field);
	smiley.setPosition(0, 0);
	goal.setPosition(4 * pixel_field, 4 * pixel_field);
	wink.setPosition(4 * pixel_field, 4 * pixel_field);

	
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

	
	while (window.isOpen())
	{
		sf::Event e;

		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed)
				window.close();
			break;


		}

		if(parameters::visual_output){
			//Draw field
			window.clear();
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					window.draw(field[i][j]);
				}
			}
		}
		

		//One of the key function: Make move depending on probability estimation from teached values
		smiley = functions::make_probabilistic_move(smiley,new_values);
		int index = functions::get_index(smiley.getPosition().x, smiley.getPosition().y);
		previous_positions.push_back(index);
		double_indices = functions::get_double_indices(previous_positions);

		//wait for next step (for visualization)
		std::chrono::milliseconds timespan(time_scale);
		std::this_thread::sleep_for(timespan);

		
		
		if (smiley.getPosition() == fire.getPosition() || smiley.getPosition() == fire2.getPosition()) {

			for (int i = 0; i < double_indices.size(); i++) {

				int double_index = double_indices[i];
				previous_positions[double_index] = 0;

			}

			for (int i = previous_positions.size()-1; i > 0; i--) {

				int foo = previous_positions[i];
				int test = previous_positions.size()-i;
				double value_assign= -1 + 0.04*test;
				new_values[foo] = new_values[foo] +  value_assign;

			}

			functions::write_in_file(new_values);
			
			if (smiley.getPosition() == fire.getPosition()) {
				window.draw(suspicious);
			}
			else{
				window.draw(suspicious2);
			}
			
			window.draw(goal);
			window.display();
			cout << "YOU LOSE! NOOB!" << endl;
			lose++;
			
			if(use_loop_keys){
				cout << "press any key to continue" << endl;
				cin >> loop_key;
			}

			window.close();

		}

		if (smiley.getPosition() == goal.getPosition()) {

			for (int i = 0; i < double_indices.size(); i++) {

				int double_index = double_indices[i];
				previous_positions[double_index] = 0;

			}

		/*	int test = previous_positions[previous_positions.size() - 1];
			new_values[previous_positions[previous_positions.size() - 1]] = new_values[previous_positions[previous_positions.size() - 1]] + 1;*/

			for (int i = previous_positions.size()-1; i > 0; i--) {

				int foo = previous_positions[i];
				int test = previous_positions.size()-i;
				double value_assign = 1 - 0.04*(test);
				new_values[foo] = new_values[foo] + value_assign;

			}

			functions::write_in_file(new_values);

			//music_goal.play();
			window.draw(fire);
			window.draw(wink);
			window.display();
			cout << "U'RE A CHAMP!!!" << endl;
			win++;
			
			if (use_loop_keys) {
				cout << "press any key to continue" << endl;
				cin >> loop_key;
			}
			window.close();

		}
		
		//if(use_step_keys){
		//	if (e.type == sf::Event::KeyPressed)
		//		if (e.key.code == sf::Keyboard::Space)
		//		{
		//			fire = functions::make_probabilistic_move(smiley);
		//			std::chrono::seconds timespan(5); // or whatever
		//			std::this_thread::sleep_for(timespan);

		//	

		//		}
		//}
	
		window.draw(smiley);
		window.draw(fire);
		window.draw(fire2);
		window.draw(goal);
		window.display();

	
	

	}
	

	CloseConnection();
	}

	cout << "win: " << win << endl;
	cout << "lose: " << lose << endl;
	cout << "win percentage: " << win / (win + lose) << endl;
	cout << "____________________" << endl;
	std::chrono::seconds timespan(1000);

	std::this_thread::sleep_for(timespan);
	return 0;
}

