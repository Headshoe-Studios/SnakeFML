#include "Snake.hpp"
#include "Mouse.hpp"

int main()
{
	//hardcode size for now...
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	//limit to 60 for now. Coil whine is annoying
	window.setFramerateLimit(60);

	//our snake and mouse
	Snake snake;
	Mouse mouse(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					mouse.respawn();
					break;
				}
			}
		}

		window.clear(sf::Color::Green); // green because... grass?
		window.draw(snake);
		window.draw(mouse);
		window.display();
	}

	return 0;
};