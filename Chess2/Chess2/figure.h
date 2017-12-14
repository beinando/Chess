#include "Functions.hpp"

using namespace functions;

class figure
{
public:
	figure();
	figure(int type);
	figure(int type, int position, bool color);
	int position;
	sf::Texture texture;
	int type;
	sf::Sprite sprite;
	int figure_x;
	int figure_y;
	vector<int> calculate_allowed_fields(int type, int position);
	int make_random_figure_move(figure input_fig);


	~figure();
};

