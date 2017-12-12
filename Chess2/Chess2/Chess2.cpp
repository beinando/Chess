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

	
	vector<double> values;
	vector<double> new_values;
	vector<int> previous_positions;

	

	//functions::zeroes_in_file();
	values = functions::read_from_file();

	for (int i = 0; i < values.size(); i++) {
		new_values.push_back(values[i]);
	}
	



	int any_key;
	
	sf::RenderWindow window(sf::VideoMode(5*56, 5*56), "MattseChess!");
	
	sf::Texture t1;
	sf::Texture t2;
	sf::Texture _goal;
	sf::Texture _fire;
	sf::Texture _smiley;
	sf::Texture _suspicious;
	sf::Texture _wink;

	_fire.loadFromFile("images/fire.png");
	_goal.loadFromFile("images/racing.png");
	_smiley.loadFromFile("images/thinking.png");
	_suspicious.loadFromFile("images/suspicious.png");
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
	sf::Sprite smiley(_smiley);
	sf::Sprite goal(_goal);
	sf::Sprite suspicious(_suspicious);
	sf::Sprite wink(_wink);

	suspicious.setPosition(0* 56, 3 * 56);
	fire.setPosition(0 * 56, 3 * 56);
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
		int index = smiley.getPosition().x / 56 + smiley.getPosition().y / 56 * 5;
		previous_positions.push_back(index);
		/*int checker = 0;
		for (int i = 0; i < previous_positions.size(); i++) {
			if (index != previous_positions[i]) {


			}
			else if (index == previous_positions[i]) {

				checker = 1;
			}
		}
			
		if (checker == 0) {
			previous_positions.push_back(index);
		}*/
		

		cout << previous_positions.back() << endl;

		
		
		smiley = functions::make_random_move(smiley);
		std::chrono::milliseconds timespan(100); 

		std::this_thread::sleep_for(timespan);

		

		if (smiley.getPosition() == fire.getPosition()) {

			new_values[previous_positions[previous_positions.size() - 1]] = new_values[previous_positions[previous_positions.size() - 1]] - 1;

			/*for (int i = previous_positions.size()-1; i > 0; i--) {

				int foo = previous_positions[i];
				int test = previous_positions.size()-i;
				double value_assign= -1 + 0.04*test;
				new_values[foo] = new_values[foo] +  value_assign;

			}*/

			functions::write_in_file(new_values);
			
			music_explosion.play();
			window.draw(suspicious);
			window.draw(goal);
			window.display();
			cout << "YOU LOSE! NOOB!" << endl;
			
			/*cout << "press any key to continue" << endl;
			cin >> any_key;*/
			window.close();

		}

		if (smiley.getPosition() == goal.getPosition()) {

			new_values[previous_positions[previous_positions.size() - 1]] = new_values[previous_positions[previous_positions.size() - 1]] + 1;

			/*for (int i = previous_positions.size() - 1; i > 0; i--) {

				int foo = previous_positions[i];
				int test = i-previous_positions.size();
				double value_assign = 1 - 0.04*(test);
				new_values[foo] = new_values[foo] + value_assign;

			}*/

			functions::write_in_file(new_values);

			music_goal.play();
			window.draw(fire);
			window.draw(wink);
			window.display();
			cout << "U'RE A CHAMP!!!" << endl;
			
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
		music.play();
		window.draw(smiley);
		window.draw(fire);
		window.draw(goal);
		window.display();

	
	

	}
	

	CloseConnection();
	return 0;
}

