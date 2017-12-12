#include "Functions.hpp"


using namespace std;
using namespace sf;

namespace functions {
	//generate random int from -1 to +1
	int generate_random_number() {

		std::mt19937 rng;
		rng.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 2); // distribution in range [1, 6]

		return (int)dist6(rng) - 1;


	}
	//generate random move
	Sprite make_random_move(Sprite player) {

		int x = player.getPosition().x;
		int y = player.getPosition().y;
		bool trigger = false;
		int new_x = 0, new_y = 0;

		while (trigger == false) {

			int rand1 = functions::generate_random_number();
			int rand2 = functions::generate_random_number();

			if ((rand1 != 0) && (rand2 == 0)) {

				new_x = x + 56 * rand1;
				new_y = y;

				if ((new_x<0) || (new_x>(4 * 56))) {
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

				if ((new_y < 0) || (new_y >(4 * 56))) {
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
	//Read values
	vector<double> read_from_file() {

		vector<double> values;
		int i = 0;
		string line;
		fstream myfile("example.txt", std::ios_base::in);

		if (myfile.is_open())
		{
			while (getline(myfile, line))
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
			for (int i = 0; i<values.size(); i++) {
				myfile << values[i] << "\n";

			}
			//to fix some reading/writing bugs, more tomorrow
			myfile << 0 << "\n";
			myfile.close();
		}
		else{
			cout << "Unable to open file";
		}

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



}
