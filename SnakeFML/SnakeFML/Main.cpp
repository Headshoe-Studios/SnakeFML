#include <iostream>
#include "Snake.hpp"
#include "MouseSpawner.hpp"
#include <SFML/Window.hpp>

#include "Button.h"

int main()
{
	enum E_GAME_STATE {
		MENU = 0,
		INGAME = 1,

		CLOSING = 42, // I find this better than forcing a shutdown with window.close() as it prevent's the current execution of the main loop to do strange things, because of the window being closed
	} gameState = MENU; // Start the game out in the menu


	//hardcode size for now...
	sf::RenderWindow window(sf::VideoMode(800, 800), "SnakeFML");

	float dt = 0; // Delta-Time
	sf::Clock dtClock;

	//limit to 60 for now. Coil whine is annoying
	window.setFramerateLimit(60);


	// Our menu
	Button playButton([&]() {
		gameState = INGAME;
	});
	playButton.shape.setSize({ 128 * 3 , 128 });
	playButton.shape.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.f - playButton.shape.getSize() / 2.f); // Center the button

	Button exitButton([&]() {
		gameState = CLOSING;
	});
	exitButton.shape.setSize({ 128 * 3, 128 });
	exitButton.shape.setPosition(playButton.shape.getPosition() + sf::Vector2f( 0, 192 )); // Magic numbers yay

	// I guess add a background here
	// sf::RectangleShape background;


	//our snake
	Snake snake(&window);

	//mouse spawner
	MouseSpawner spawner(&window);

	while (gameState != CLOSING)
	{
		dt = dtClock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				gameState = CLOSING;
			}

			switch (gameState) {
			case E_GAME_STATE::MENU:
				playButton.processEvent(event);
				exitButton.processEvent(event);
				break;
			default:
				break;
			}
		}

		window.clear(sf::Color(0, 128, 0));

		switch (gameState) {
		case E_GAME_STATE::INGAME:
			//update snake
			snake.update(dt);

			spawner.checkCollisions(snake);
			spawner.spawn();

			window.draw(snake);
			spawner.draw();
			break;
		case E_GAME_STATE::MENU:
			window.draw(playButton.shape);
			window.draw(exitButton.shape);
			break;
		default:
			break;
		}
		window.display();
	}
	window.close();

	return 0;
};
