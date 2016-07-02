#include <iostream>
#include <SFML/Window.hpp>

#include "Snake.hpp"
#include "MouseSpawner.hpp"
#include "World.hpp"
#include "Score.hpp"
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
    icon.loadFromFile("Assets/Images/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sf::Clock	dtClock;

    //Objects
    Options         options;
    Score			score("KBZipaDeeDooDah.ttf");
    World			world("Assets/Images/Grass.png", { 1000,1000 });
    Snake			snake(window,world,score,"Assets/Images/SnakeHead.png");
    MouseSpawner	spawner(&window,"Assets/Images/Mouse.png", snake);

    sfg::SFGUI sfgui;
    sfg::Desktop desktop;

    auto movingCameraWidget = sfg::CheckButton::Create("Camera follows snake");
    movingCameraWidget->SetActive(options.getMovingCamera());
    movingCameraWidget->SetClass("Options");
    auto snakeSpeedWidget = sfg::SpinButton::Create(100.f, 400.f, 5.f);
    snakeSpeedWidget->SetValue(snake.getSpeed());
    snakeSpeedWidget->SetClass("Options");
    auto snakeSpeedLabel = sfg::Label::Create("Snake speed:");
    snakeSpeedLabel->SetClass("Options");
    auto hbox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    hbox->Pack(snakeSpeedLabel);
    hbox->Pack(snakeSpeedWidget);
    auto doneButton = sfg::Button::Create("Done");
    doneButton->SetClass("Options");
    auto vbox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 20.f);
    vbox->Pack(movingCameraWidget);
    vbox->Pack(hbox);
    vbox->Pack(doneButton);
    auto optionsWidget = sfg::Window::Create(sfg::Window::NO_STYLE);
    optionsWidget->SetTitle("Options");
    optionsWidget->Add(vbox);
    optionsWidget->SetPosition({100.f, 200.f});
    optionsWidget->Show(false);
    desktop.Add(optionsWidget);

    auto menuBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

    menuBox->SetPosition({50, 50});
    desktop.Add(menuBox);

    desktop.SetProperty(".Options", "FontSize", "50" );
    desktop.SetProperty(".Options", "BackgroundColor", "#00000000" );
    desktop.SetProperty("SpinButton", "StepperBackgroundColor", "#00000000" );
    desktop.SetProperty("*", "FontName", "KBZipaDeeDooDah.ttf" );

    auto makeMenuButton = [&desktop, &menuBox](const std::string& name, std::function< void()> delegate){
        auto button = sfg::Button::Create(name);
        button->SetId(name);
        button->GetSignal(sfg::Button::OnLeftClick).Connect(std::move(delegate));

        menuBox->Pack(button);

        auto id = "#"+name;
        desktop.SetProperty( id, "FontSize", "200" );

        desktop.SetProperty( id, "BackgroundColor", "#00000000" );
        desktop.SetProperty( id, "BorderColor", "#00000000" );
    };

    makeMenuButton("Play", [&currentState, menuBox]{
        currentState = INGAME;
        menuBox->Show(false);
    });
    makeMenuButton("Options", [optionsWidget, menuBox]{
        menuBox->Show(false);
        optionsWidget->Show(true);
    });
    makeMenuButton("Quit", [&currentState, menuBox]{
        currentState = EXITING;
    });

    doneButton->GetSignal(sfg::Button::OnLeftClick).Connect([optionsWidget,
                                                             movingCameraWidget,
                                                             snakeSpeedWidget,
                                                             menuBox,
                                                            &options,
                                                            &snake]
    {
        menuBox->Show(true);
        optionsWidget->Show(false);
        options.setMovingCamera(movingCameraWidget->IsActive());
        snake.setSpeed(snakeSpeedWidget->GetValue());
    });

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
                //menu.handleEvent(event);
                break;
            case INGAME:
                if (event.type == sf::Event::KeyPressed)
                {
                    switch (event.key.code)
                    {
                    //escape to pause
                    case sf::Keyboard::Escape:
                        currentState = MENU;
                        menuBox->Show(true);
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
        if (currentState != MENU){
            window.setView(window.getDefaultView());
            window.draw(score);
        }

        //		if (currentState == MENU)
        //			window.draw(menu);

        sfgui.Display(window);

        window.display();
        sf::sleep(sf::seconds(0));
    }
    window.close();

    return 0;
};
