#include "Functions.hpp"


/*	cout << "index: " << index << endl;
cout << "value: " << values[index] << endl;
cout << "maximum: " << maximum << endl;
cout << "rel. maximum: " << rel_max << endl;
cout << "rel. value: " << (values[index]/mean) << endl;
cout << "difference: " << difference << endl;
cout << "______________" << endl;
cout << "new dicing " << dice_this / (100 * mean) << endl;*/

using namespace std;
using namespace sf;
using namespace parameters;

namespace functions {

	////////////////////////////////////
	//////mathematical functions////////
	////////////////////////////////////

	int get_index(int x, int y) {
		int index = size_board*y+x;
		return index;
	}

	double get_max(vector<double> values) {

		double max = 0;

		for (int i = 1; i < values.size(); i++) {
			if (values[i] > max) {
				max = values[i];
			}
		}
		return max;
	}

	double get_min(vector<double> values) {

		double min = 1e7;

		for (int i = 1; i < values.size(); i++) {
			if (values[i] < min) {
				min = values[i];
			}
		}
		return min;
	}

	double get_mean(vector<double> values) {

		double sum = 0;

		for (int i = 1; i < values.size(); i++) {
				sum = sum+values[i];
		}
		return (sum/values.size());
	}

	//generate random int from start to end
	int generate_random_number(int start, int end) {

		std::mt19937 rng;
		rng.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(start, end); // distribution in range [1, 6]

		return (int)dist6(rng);

	}

	int get_x_index_from_position(int position) {

		return (position%size_board);

	}
	int get_y_index_from_position(int position) {

		return (position / size_board);

	}

	int get_x_from_position(int position) {

		return (position%size_board)*pixel_field;

	}


	int get_y_from_position(int position) {

		return (position/size_board)*pixel_field;

	}

	////////////////////////////////////
	//////OTHERS////////////////////////
	////////////////////////////////////
	void sleep(int milliseconds) {

		std::chrono::milliseconds timespan(milliseconds);

		std::this_thread::sleep_for(timespan);

	}

	



	////////////////////////////////////
	//////READ-WRITE FUNCTIONS//////////
	////////////////////////////////////

	//Read values
	vector<double> read_from_file(vector<double> dummy_vec) {

		vector<double> values;
		ifstream in_file;
		in_file.open("list.txt");

		//check for error
		if (in_file.fail()) {

			cerr << "Error opening file" << endl;
			exit(1);
		}

		int count = 0;
		double dummy;
		while (count<dummy_vec.size()) {

			in_file >> dummy;
			values.push_back(dummy);
			count++;
		}
		in_file.close();
		return values;
	}

	void write_in_file(vector<double> values) {

		ofstream out_file;
		out_file.open("list.txt");
		int count = 0;

		while (count < values.size())
		{
			out_file << values[count] << "\n";
			count++;
		}
		out_file.close();

	}


	void zeroes_in_file(vector<double> start_vector) {



		ofstream out_file;
		out_file.open("list.txt");

		int count = 0;


		while (count < start_vector.size())
		{

			out_file << 0.2 << "\n";
			count++;
		}


		out_file.close();

	}

	vector<int> get_double_indices(vector<int> prev_positions) {

		vector<int> double_entries;

		for (int i = 0; i < prev_positions.size() - 1; i++) {

			int compare_value = prev_positions[i];

			for (int j = i + 1; j < prev_positions.size(); j++) {

				int compare_value2 = prev_positions[j];

				if (compare_value == compare_value2) {

					double_entries.push_back(i);


				}
			}
		}



		return double_entries;
	}
	
	////////////////////////////////////
	//////FUNCTIONS FOR THE GAME////////
	////////////////////////////////////


	Sprite make_random_move(Sprite player) {

		int x = player.getPosition().x;
		int y = player.getPosition().y;
		bool trigger = false;
		int new_x = 0, new_y = 0;

		while (trigger == false) {

			int rand1 = functions::generate_random_number(0,2)-1;
			int rand2 = functions::generate_random_number(0,2)-1;

			if ((rand1 != 0) && (rand2 == 0)) {

				new_x = x + 56 * rand1;
				new_y = y;

				if ((new_x < 0) || (new_x > (4 * 56))) {
					new_x = x;
					new_y = y;
				}
				else {
					trigger = true;
				}
			}

			else if ((rand1 == 0) && (rand2 != 0)) {

				new_x = x;
				new_y = y + 56 * rand2;

				if ((new_y < 0) || (new_y > (4 * 56))) {
					new_x = x;
					new_y = y;
				}
				else {
					trigger = true;
				}
			}
			else {
				new_x = x;
				new_y = y;
			}
		}

		player.setPosition(new_x, new_y);
		return player;

	}

	//generate random move with probabilities from value-vector
	Sprite make_probabilistic_move(Sprite player, vector<double> values) {

		int index = get_index(player.getPosition().x, player.getPosition().y);

		double maximum = get_max(values);
		double minimum = get_min(values);
		
		int x = player.getPosition().x;
		int y = player.getPosition().y;
		bool trigger = false;
		int new_x = 0, new_y = 0;

		while (trigger == false) {

			int rand1 = functions::generate_random_number(0,2)-1;
			int rand2 = functions::generate_random_number(0,2)-1;

			if ((rand1 != 0) && (rand2 == 0)) {

				new_x = x + 56 * rand1;
				new_y = y;

				if ((new_x < 0) || (new_x >(4 * 56))) {
					new_x = x;
					new_y = y;
				}
				else {

					double index=get_index(new_x, new_y);
				
					//this here is around for setting up negative values to zero, means adding the minimal value to the vector entries
					int dice_this = generate_random_number(0, int((maximum + abs(minimum)) * 100000));
					int tester = (values[index] + abs(minimum)) * 100000;
					if (dice_this <= (values[index]+abs(minimum))* 100000 - offset_dicing) {
						trigger = true;
					}
					else {
						new_x = x;
						new_y = y;
					}
				}
			}

			else if ((rand1 == 0) && (rand2 != 0)) {

				new_x = x;
				new_y = y + 56 * rand2;

				if ((new_y < 0) || (new_y >(4 * 56))) {
					new_x = x;
					new_y = y;
				}
				else {
					double index = get_index(new_x, new_y);
					
					//this here is around for setting up negative values to zero, means adding the minimal value to the vector entries
					int dice_this = generate_random_number(0, int((maximum+abs(minimum))*100000));
					double tester = (values[index] + abs(minimum)) * 100000;

					if (dice_this<= (values[index] + abs(minimum)) *100000- offset_dicing) {
						trigger = true;
					}
					else {
						new_x = x;
						new_y = y;
					}
				}
			}
			else {
				new_x = x;
				new_y = y;
			}
		}

		player.setPosition(new_x, new_y);
		return player;


	}



	

}

