#include <iostream>
#include <SFML/Window.hpp>

#include "Snake.hpp"
#include "MouseSpawner.hpp"
#include "World.hpp"
#include "Button.hpp"
#include "Score.hpp"
#include "Menu.hpp"
#include "Options.hpp"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

int main()
{
	//state
	enum gameState
	{
		MENU,
		INGAME,
		EXITING
	} currentState(MENU); //launch into menu

	//window and framerate control
	sf::RenderWindow window(sf::VideoMode(800, 800), "SnakeFML");
	window.setFramerateLimit(60);
	sf::Image icon;
	icon.loadFromFile("Icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	sf::Clock	dtClock;

	//Objects
    Options         options;
	Score			score("KBZipaDeeDooDah.ttf");
	World			world("Grass.png", { 1000,1000 });
    Snake			snake(window,world,score,"SnakeHead.png", options);
	MouseSpawner	spawner(&window,"Mouse.png", snake);
	Button			playButton([&]() {currentState = INGAME; }, "PlayButton.png");
	Button			quitButton([&]() {currentState = EXITING; }, "QuitButton.png");
	Menu			menu(window,{ playButton, quitButton });

    sfg::SFGUI sfgui;
    sfg::Desktop desktop;

    auto movingCameraWidget = sfg::CheckButton::Create("Camera follows snake");
    auto snakeSpeedWidget = sfg::SpinButton::Create(100.f, 200.f, 5.f);
    auto snakeSpeedLabel = sfg::Label::Create("Snake speed:");
    auto vbox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    vbox->Pack(movingCameraWidget);
    vbox->Pack(snakeSpeedLabel);
    vbox->Pack(snakeSpeedWidget);
    auto optionsWidget = sfg::Window::Create();
    optionsWidget->SetTitle("Options");
    optionsWidget->Add(vbox);
    desktop.Add(optionsWidget);

	while (window.isOpen())
	{
		if (currentState == EXITING)
		{
			window.close();
			continue;
		}
		auto dt(dtClock.restart().asSeconds());
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				currentState = EXITING;
			}

			switch (currentState)
			{
			case MENU:
                desktop.HandleEvent(event);
				menu.handleEvent(event);
				break;
			case INGAME:
				if (event.type == sf::Event::KeyPressed)
				{
					switch (event.key.code)
					{
						//escape to pause
					case sf::Keyboard::Escape:
						currentState = MENU;
						break;
					default:
						break;
					}
				}
				break;
			default:
				break;
			}
		}

        desktop.Update(dt);

		window.clear(sf::Color(50,150, 255));	//because Sea!

		if (currentState == INGAME)
		{
			//update objects if in game (i.e. not paused)
			snake.update(dt);
			spawner.checkCollisions();
			spawner.spawn();
		}

		//draw the essentials (with the correct view)
        if (options.getMovingCamera())
            window.setView(snake.getView());
		window.draw(world);
		spawner.draw();
		window.draw(snake);

		//default view for score (and menu, if needed)
		window.setView(window.getDefaultView());
		window.draw(score);

		if (currentState == MENU)
			window.draw(menu);

        sfgui.Display(window);

		window.display();
		sf::sleep(sf::seconds(0));
	}
	window.close();

	return 0;
};
