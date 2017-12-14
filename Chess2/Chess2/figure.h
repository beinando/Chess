#include "Functions.hpp"

using namespace functions;

class figure
{
public:
	figure();
	figure(int type);
	figure(int type, int position);
	int position;
	sf::Texture texture;
	int type;
	sf::Sprite sprite;
	int figure_x;
	int figure_y;

	~figure();
};

