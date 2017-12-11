#include <SFML/Graphics.hpp>
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

using namespace sf;
using namespace std;



int generate_random_number() {

	std::mt19937 rng;
	rng.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 2); // distribution in range [1, 6]

	return (int)dist6(rng)-1;
	

}

Sprite make_random_move(Sprite player) {


	int x = player.getPosition().x;
	int y = player.getPosition().y;

	int rand1= generate_random_number();
	int rand2 = generate_random_number();

	int new_x=0, new_y=0;

	

	if((rand1!=0) && (rand2==0)){
 	new_x = x + 56 * rand1;
	new_y = y;
	}
	else if ((rand1==0) && (rand2 != 0)){
  	new_x = x;
	new_y = y + 56 * rand2;
	}

	else{
 		new_x = x; 
		new_y = y;
		make_random_move(player);
		
		
	}

	if (new_x < 0 || new_y < 0 || new_x > 4*56 || new_y > 4*56) {

		new_x = x;
		new_y = y;
		make_random_move(player);

	}

	player.setPosition(new_x, new_y);

	return player;
}
vector<double> read_from_file(){
	
	vector<double> values;
	 
	int i = 0;

	string line;
	fstream myfile("example.txt", std::ios_base::in);
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
			double a;
			while (myfile >> a)
			{
				values.push_back(a);
				printf("%f ", values[i]);
				i++;
			}
		}
		myfile.close();
	}
	

	return values;
}

void write_in_file(vector<double> values) {
	
	ofstream myfile("example.txt");

	if (myfile.is_open())
	{
		for(int i=0; i<values.size(); i++){
		myfile << values[i] <<	"\n";

		}
		//to fix some reading/writing bugs, more tomorrow
		myfile << 0 << "\n";
		

		myfile.close();
	}
	else cout << "Unable to open file";
	


	
}

void zeroes_in_file() {

	ofstream myfile("example.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i<26; i++) {
			myfile << 0 << "\n";

		}


		myfile.close();
	}
	else cout << "Unable to open file";




}




int main() {

	
	vector<double> values;
	vector<double> new_values;
	vector<int> previous_positions;

	

	//zeroes_in_file();
	values = read_from_file();

	for (int i = 0; i < values.size(); i++) {
		new_values.push_back(values[i]);
	}
	



	int any_key;
	int random_x = generate_random_number();
	int random_y = generate_random_number();

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

		int checker = 0;
		for (int i = 0; i < previous_positions.size(); i++) {
			if (index != previous_positions[i]) {


			}
			else if (index == previous_positions[i]) {

				checker = 1;
			}
		}
			
		if (checker == 0) {
			previous_positions.push_back(index);
		}
		

		cout << previous_positions.back() << endl;

		smiley = make_random_move(smiley);
		std::chrono::milliseconds timespan(1); 

		std::this_thread::sleep_for(timespan);

		if (smiley.getPosition() == fire.getPosition()) {

			for (int i = previous_positions.size()-1; i > 0; i--) {

				int foo = previous_positions[i];
				int test = previous_positions.size()-i;
				double value_assign= -1 + 0.04*test;
				new_values[foo] = new_values[foo] +  value_assign;

			}

			write_in_file(new_values);
			
			
			window.draw(suspicious);
			window.draw(goal);
			window.display();
			cout << "YOU LOSE! NOOB!" << endl;
			/*cout << "press any key to continue" << endl;
			cin >> any_key;*/
			window.close();

		}

		if (smiley.getPosition() == goal.getPosition()) {


			for (int i = previous_positions.size() - 1; i > 0; i--) {

				int foo = previous_positions[i];
				int test = i-previous_positions.size();
				double value_assign = 1 - 0.04*(test);
				new_values[foo] = new_values[foo] + value_assign;

			}

			write_in_file(new_values);

			
			window.draw(fire);
			window.draw(wink);
			window.display();
			cout << "U'RE A CHAMP!!!" << endl;
			/*cout << "press any key to continue" << endl;
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
		window.draw(smiley);
		window.draw(fire);
		window.draw(goal);
		window.display();

	
	

	}
	

	CloseConnection();
	return 0;
}

