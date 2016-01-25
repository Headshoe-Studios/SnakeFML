#include "MouseSpawner.hpp"
#include "Mouse.hpp"
#include <chrono>
#include <functional>
#include <iostream>

constexpr std::uint8_t maximumSpawnedMice()
{
    return 10;
}

constexpr float spawnInterval()
{
    return 1.f;
}

MouseSpawner::MouseSpawner(sf::RenderWindow* window) :
randomEngine(),
xDistribution(),
yDistribution(),
spawnedMice(),
spawnTimer(),
window(window),
nextId(0),
active(true)
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	randomEngine.seed(seed);

	// Currently uses window size
	auto size = window->getSize();
	xDistribution = std::uniform_int_distribution<int>(0, size.x);
	yDistribution = std::uniform_int_distribution<int>(0, size.y);
}

void MouseSpawner::spawn()
{

	if (spawnTimer.getElapsedTime().asSeconds() >= spawnInterval())
	{
	    spawnTimer.restart();

	    if (active && spawnedMice.size() < maximumSpawnedMice())
	    {
            std::unique_ptr<Mouse> mouse = std::make_unique<Mouse>(nextId);

            auto xPosition = xDistribution(randomEngine);
            auto yPosition = yDistribution(randomEngine);

            mouse->setBodyPosition(xPosition, yPosition);

            spawnedMice.emplace(nextId, std::move(mouse));

            ++nextId;
	    }
	}
}

void MouseSpawner::checkCollisions(Snake& snake)
{
	for (auto mouse = spawnedMice.begin(); mouse != spawnedMice.end(); ++mouse)
	{
        if(snake.checkForCollision(mouse->second->getBodyPosition(), mouse->second->getBodySize()))
        {
			snake.addToSize(mousePointValue);
            mouse = spawnedMice.erase(mouse);
			if (mouse == spawnedMice.end())
			{
				break;
			}
		}
    }
}

void MouseSpawner::draw() const
{
    for (auto& mouse : spawnedMice)
    {
        window->draw(*mouse.second);
    }
}
