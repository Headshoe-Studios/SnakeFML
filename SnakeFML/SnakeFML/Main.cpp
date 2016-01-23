#include <iostream>
#include "Snake.hpp"
#include "MouseSpawner.hpp"
#include <SFML/Window.hpp>

int main()
{
	//hardcode size for now...
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	//limit to 60 for now. Coil whine is annoying
	window.setFramerateLimit(60);

	//measure dt
	sf::Clock dtClock;

	//our snake
	Snake snake(&window);

	//mouse spawner
	MouseSpawner spawner(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//update snake
		snake.update(dtClock.restart().asSeconds());

		spawner.checkCollisions(snake);

        window.clear(sf::Color(0,128,0)); // green because... grass?
		window.draw(snake);
	    spawner.draw();
		window.display();
	}

	return 0;
};
