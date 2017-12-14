#include "figure.h"


class field
{
public:
	field();
	field(int index, int state, int number_attacked_by);
	int index;
	int state;
	int number_attacked_by;
	int calculate_attacked_by(int index, vector<int> figure_allowed_moves);
	

	~field();
};

