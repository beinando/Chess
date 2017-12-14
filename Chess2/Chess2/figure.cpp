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
figure::figure(int type, int position, bool color)
{

	switch (type) {
	case 3:
		if(color==true){
			
		sf::Texture rook;
		rook.loadFromFile("images/WhiteRook.png");
		figure::texture = rook;

		
		}
		else{
			sf::Texture rook;
			rook.loadFromFile("images/BlackRook.png");
			figure::texture = rook;
		}
	case 5:
		if (color == true) {
			sf::Texture rook;
			rook.loadFromFile("images/WhiteKing.png");
		}
		else {
			sf::Texture rook;
			rook.loadFromFile("images/BlackKing.png");
		}

	}


	figure_x = get_x_from_position(position);
	figure_y = get_y_from_position(position);


}


vector<int> figure::calculate_allowed_fields(int type, int position) {

	vector<int> allowed_positions;
	allowed_positions.clear();
	figure_x = get_x_index_from_position(position);
	figure_y = get_y_index_from_position(position);

	for (int x = 0; x < parameters::size_board; x++) {

		if (x == figure_x) {



		}

		else {
			int test = get_index(x, figure_y);
			allowed_positions.push_back((get_index(x,figure_y)));
		}

	}

	for (int y = 0; y < parameters::size_board; y++) {

		if (y == figure_y) {


		}

		else {
			int test = get_index(figure_x, y);
			allowed_positions.push_back((get_index(figure_x, y)));
		}

	}




	return allowed_positions;
	



}

int figure::make_random_figure_move(figure input_fig) {

	vector<int> allowed_fields = input_fig.calculate_allowed_fields(0, input_fig.position);

	int random = generate_random_number(0, allowed_fields.size()-1);
	//
	

	return allowed_fields[random];


}







figure::~figure()
{
}
