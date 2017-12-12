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

using namespace sf;
using namespace std;

//measure performance

/*	auto start = chrono::steady_clock::now();
auto end = chrono::steady_clock::now();
double elapsed_time = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());*/










int main() {
	int win = 0;
	int lose = 0;
	int time_step = 50;
	for(int i=0; i<1000;i++){
	int start_vector_size=25;
	vector<int> double_indices;
	vector<double> start_vector;
	
	
	for (int i = 0; i < start_vector_size; i++) {
		start_vector.push_back(0);
		
	}


	
	//Rewrite values file with zeroes
	//functions::zeroes_in_file(start_vector);

	vector<double> values;
	vector<double> new_values;
	vector<int> previous_positions;

	values = functions::read_from_file(start_vector);

	new_values = values;

	functions::write_in_file(new_values);
	



	int any_key;
	
	
	sf::RenderWindow window(sf::VideoMode(5*56, 5*56), "MattseChess!");
	
	sf::Texture t1;
	sf::Texture t2;
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

	Music music;
	Music music_explosion;
	Music music_goal;
	if (!music.openFromFile("audio/Blip_Select4.ogg")){
		return -1; // error
	}

	if (!music_explosion.openFromFile("audio/Explosion20.ogg")) {
		return -1; // error
	}
	if (!music_goal.openFromFile("audio/Powerup15.ogg")) {
		return -1; // error
	}
	

	

	


	if (!t1.loadFromFile("images/whitefield.png") || !t2.loadFromFile("images/blackfield.png")) {


		std::cout << "Error loading texture" << std::endl;

	}


	sf::Sprite fire(_fire);
	sf::Sprite fire2(_fire2);
	sf::Sprite smiley(_smiley);
	sf::Sprite goal(_goal);
	sf::Sprite suspicious(_suspicious);
	sf::Sprite suspicious2(_suspicious2);
	sf::Sprite wink(_wink);

	suspicious.setPosition(2* 56, 2 * 56);
	suspicious2.setPosition(0 * 56, 4 * 56);
	fire.setPosition(2 * 56, 2 * 56);
	fire2.setPosition(0 * 56, 4 * 56);
	smiley.setPosition(0, 0);
	goal.setPosition(4 * 56, 4 * 56);
	wink.setPosition(4 * 56, 4 * 56);

	
	sf::Sprite field[5][5];
	//set sprites for fields
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {

			if ((i + j) % 2 == 0) {
				field[i][j] = sf::Sprite(t1);
			}
			else {
				field[i][j] = sf::Sprite(t2);
			}
			
			field[i][j].setPosition(i * 56, j * 56);

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


		//Draw field
		window.clear();
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				window.draw(field[i][j]);
			}
		}
		
		
		// 5= number of fields per side
		/*cout << smiley.getPosition().x/56 << endl;
		cout << smiley.getPosition().y / 56 << endl;*/

		
		

	//	cout << previous_positions.back() << endl;


		

		//One of the key function: Make move depending on probability estimation from teached values
		smiley = functions::make_probabilistic_move(smiley,new_values);
		int index = functions::get_index(smiley.getPosition().x, smiley.getPosition().y);
		previous_positions.push_back(index);
		double_indices = functions::get_double_indices(previous_positions);

	//	smiley = functions::make_random_move(smiley);
		std::chrono::milliseconds timespan(time_step); 

		std::this_thread::sleep_for(timespan);

		
		
		if (smiley.getPosition() == fire.getPosition() || smiley.getPosition() == fire2.getPosition()) {

			for (int i = 0; i < double_indices.size(); i++) {

				int double_index = double_indices[i];
				previous_positions[double_index] = 0;

			}


		/*	int test = previous_positions[previous_positions.size() - 1];

			new_values[previous_positions[previous_positions.size() - 1]] = new_values[previous_positions[previous_positions.size() - 1]] - 1;*/

			for (int i = previous_positions.size()-1; i > 0; i--) {

				int foo = previous_positions[i];
				int test = previous_positions.size()-i;
				double value_assign= -1 + 0.04*test;
				new_values[foo] = new_values[foo] +  value_assign;

			}

			functions::write_in_file(new_values);
			
			music_explosion.play();
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
			
			/*cout << "press any key to continue" << endl;
			cin >> any_key;*/
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
			
		/*	cout << "press any key to continue" << endl;
			cin >> any_key;*/
			window.close();

		}
		
		//if (e.type == sf::Event::KeyPressed)
		//	if (e.key.code == sf::Keyboard::Space)
		//	{
		//		fire = make_random_move(fire);
		//		std::chrono::seconds timespan(5); // or whatever

		//		std::this_thread::sleep_for(timespan);

		//	

		//	}
		//music.play();
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

