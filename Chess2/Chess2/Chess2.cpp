#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>


int main() {

	sf::RenderWindow window(sf::VideoMode(437, 437), "MattseChess!");

	sf::Texture t1;
	if (!t1.loadFromFile("figures.png")) {


		std::cout << "Error loading texture" << std::endl;
	}
	sf::Sprite s(t1);

	while (window.isOpen())
	{
		sf::Event e;

		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed)
				window.close();
			break;



			//Draw
			window.clear();
			window.draw(s);
			window.display();



		}






	}

	return 0;
}
