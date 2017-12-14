#include "field.h"



field::field()
{
	field::index = 0;
	field::state = 0;
	field::number_attacked_by = 0;


}


field::field(int index, int state, int number_attacked_by)
{
	field::index = index;
	field::state = state;
	field::number_attacked_by = number_attacked_by;

}



int field::calculate_attacked_by(int index, vector<int> figure_allowed_moves) {

	int attack_by_number = 0;

	for (int i = 0; i < figure_allowed_moves.size(); i++) {


		if (figure_allowed_moves[i] == index) {

			attack_by_number++;
		}
	}

	return attack_by_number;


}

field::~field()
{
}
