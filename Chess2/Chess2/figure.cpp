#include "figure.h"


figure::figure()
{
	position = 0;
	sf::Texture t1; 
	t1.loadFromFile("images/question_mark.png");


}
//int type := type of figure 1=knight, 2=bishop, 3=rook, 4=queen, 5=king, 6=pawn (no zero because of consistency with the field status (0 = empty in field))
figure::figure(int type)
{
	position = 0;
	type = this->type;
	sf::Texture t1;
	//TODO switch for each figure
	t1.loadFromFile("images/question_mark.png");

}

//int type := type of figure 1=knight, 2=bishop, 3=rook, 4=queen, 5=king, 6=pawn (no zero because of consistency with the field status (0 = empty in field))
figure::figure(int type, int position, bool color)
{

	figure::is_alive = true;
	figure::position = position;
	figure::type = type;

	switch (type) {
	case 3:
		if(color==true){
			
		sf::Texture rook;
		rook.loadFromFile("images/WhiteRook.png");
		figure::texture = rook;
		break;

		
		}
		else if(color == false) {
			sf::Texture rook;
			rook.loadFromFile("images/BlackRook.png");
			figure::texture = rook;
			break;

		}
	case 5:
		if (color == true) {
			sf::Texture king;
			king.loadFromFile("images/WhiteKing.png");
			figure::texture = king;
		}
		else {
			sf::Texture king;
			king.loadFromFile("images/BlackKing.png");
			figure::texture = king;
		}

	}

	
	figure::figure_x = get_x_from_position(position);
	figure::figure_y = get_y_from_position(position);


}


vector<int> figure::calculate_allowed_fields(int type, int position,vector<int> board_status) {

	vector<int> allowed_positions;
	allowed_positions.clear();
	figure_x = get_x_index_from_position(position);
	figure_y = get_y_index_from_position(position);

	if (type == 3) {
	
		//for rook
		for (int x = 0; x < parameters::size_board; x++) {

			if (x == figure_x) {
			}
			else {
				int test = get_index(x, figure_y);

				if(board_status[test]==0){
					allowed_positions.push_back((get_index(x, figure_y)));
				}
			}
		}

		for (int y = 0; y < parameters::size_board; y++) {

			if (y == figure_y) {
			}
			else {
				int test = get_index(figure_x, y);
				if (board_status[test] == 0) {
					allowed_positions.push_back((get_index(figure_x, y)));
				}
			}
		}
	}
	else if (type == 5) {
		int index_x = get_x_index_from_position(position);
		int index_y = get_y_index_from_position(position);

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int test = get_index(index_x + i, index_y + j);
				if ((index_x + i >= 0) && (index_x + i < parameters::size_board) && (index_y + j >= 0) && (index_y + j < parameters::size_board) && !((i == 0) && (j == 0))) {
					if (board_status[test] == 0) {
						allowed_positions.push_back((get_index(index_x + i, index_y + j)));
					}
				}

			}
		}
	}
	

		

		



	
	figure::allowed_fields = allowed_positions;
	return allowed_positions;

}

//check for block of figures (first design, for later)
bool update_allowed_positions(vector<int> allowed_positions1, vector<int> allowed_positions2) {

	int checker = true;
	vector<int> updated_allowed_positions;
	for (int i = 0; i < allowed_positions1.size(); i++) {
		
		if (checker == true) {

			updated_allowed_positions.push_back(allowed_positions1[i]);

		}

		for (int j = 0; j < allowed_positions2.size(); j++) {

			if (allowed_positions1[i] == allowed_positions2[j]) {

				checker = false;

			}
		}
	}
	return false;

}

int figure::make_random_figure_move(int type, int position, vector<int> board_status) {

	vector<int> allowed_fields = calculate_allowed_fields(type, position, board_status);

	int random = generate_random_number(0, allowed_fields.size()-1);
	//
	

	return allowed_fields[random];


}







figure::~figure()
{
}
