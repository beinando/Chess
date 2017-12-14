#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <thread>
#include "Parameters.hpp"

using namespace sf;
using namespace std;

namespace functions{

	int get_index(int x, int y);
	double get_max(vector<double> values);
	double get_mean(vector<double> values);
	int generate_random_number();
	int generate_random_number_0_to_max();
	Sprite make_random_move(Sprite player);

	Sprite make_probabilistic_move(Sprite player,vector<double> values);
	vector<double> read_from_file(vector<double> dummy_vec);
	void write_in_file(vector<double> values);
	void zeroes_in_file(vector<double> start_vector);
	vector<int> get_double_indices(vector<int> prev_positions);
	int get_x_from_position(int position);
	int get_y_from_position(int position);
	
}
