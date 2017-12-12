#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <thread>

using namespace sf;
using namespace std;

namespace functions{

	int generate_random_number();
	Sprite make_random_move(Sprite player);
	vector<double> read_from_file();
	void write_in_file(vector<double> values);
	void zeroes_in_file();
}
