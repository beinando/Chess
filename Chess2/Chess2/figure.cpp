#include "figure.h"


figure::figure()
{
	position = 0;
	sf::Texture t1; 
	t1.loadFromFile("images/question_mark.png");


}
//int type := type of figure, 0=pawn, 1=knight, 2=bishop, 3=rook, 4=queen, 5=king
figure::figure(int type)
{
	position = 0;
	type = this->type;
	sf::Texture t1;
	//TODO switch for each figure
	t1.loadFromFile("images/question_mark.png");

}

//int type := type of figure, 0=pawn, 1=knight, 2=bishop, 3=rook, 4=queen, 5=king
figure::figure(int type, int position)
{

	figure_x = get_x_from_position(position);
	figure_y = get_y_from_position(position);


}





figure::~figure()
{
}
