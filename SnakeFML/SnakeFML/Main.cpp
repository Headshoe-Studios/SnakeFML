#include <iostream>
#include "Snake.hpp"
#include "MouseSpawner.hpp"
#include "World.h"
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
	
	//declare and load font/text for use in showing a score
	sf::Font liberationSans;
	liberationSans.loadFromFile("LiberationSans-Regular.ttf");
	sf::Text playerScore;
	playerScore.setFont(liberationSans);

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

	//World
	World world("Grass.png", { 1000,1000 });

	//our snake
	Snake snake(window,world,"SnakeHead.png");

	//mouse spawner
	MouseSpawner spawner(&window,"Mouse.png", snake);

	

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

			switch (gameState) 
			{
			case MENU:
				playButton.processEvent(event);
				exitButton.processEvent(event);
				break;
			case INGAME:
				if (event.type == sf::Event::KeyPressed)
				{
					switch (event.key.code)
					{
						//escape to pause
					case sf::Keyboard::Escape:
						gameState = MENU;
						break;
					default:
						break;
					}
				}
			default:
				break;
			}
		}

		window.clear(sf::Color(50,150, 255));	//because Sea!

		switch (gameState) {
		case E_GAME_STATE::INGAME:
			//update snake
			snake.update(dt);
			window.setView(snake.getView());
			
			//update score
			playerScore.setString(std::to_string(snake.getCurrentScore()));
			
			//check for collisions with mice
			spawner.checkCollisions();
			spawner.spawn();

			window.draw(world);
			spawner.draw();
			window.draw(snake);
			
			//set to default view to draw score
			window.setView(window.getDefaultView());
			window.draw(playerScore);
			break;
		case E_GAME_STATE::MENU:
			window.setView(window.getDefaultView());
			window.draw(playButton.shape);
			window.draw(exitButton.shape);
			break;
		default:
			break;
		}
		window.display();
		sf::sleep(sf::seconds(0));
	}
	window.close();

	return 0;
};
