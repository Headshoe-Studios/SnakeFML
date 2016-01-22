#include <SFML/Graphics.hpp>

int main()
{
	//hardcode size for now...
	sf::RenderWindow window(sf::VideoMode(800, 2800), "SFML works!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}