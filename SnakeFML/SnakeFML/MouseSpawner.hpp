#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <random>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Mouse.hpp"
#include "Snake.hpp"

class MouseSpawner final
{
public:

    MouseSpawner(sf::RenderWindow* window, std::string mouseTexture, Snake& snake);

    void spawn();
    void checkCollisions();

    void draw() const;

private:

    std::mt19937                                   randomEngine;
    std::uniform_int_distribution<int>             xDistribution;
    std::uniform_int_distribution<int>             yDistribution;
    std::map<std::uint8_t, std::unique_ptr<Mouse>> spawnedMice;
    sf::Clock                                      spawnTimer;
    sf::RenderWindow*                              window;
    std::uint8_t                                   nextId;

	Snake*										   m_snake;	
	sf::Texture									   m_mouseTexture;

	const int mousePointValue = 10;
    bool                                           active;
};
