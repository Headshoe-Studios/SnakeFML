#include "MouseSpawner.hpp"
#include "Mouse.hpp"
#include <chrono>
#include <functional>
#include <iostream>

constexpr std::uint8_t maximumSpawnedMice()
{
    return 10;
}

constexpr std::chrono::seconds spawnInterval()
{
    return std::chrono::seconds(1);
}

void spawnTimer(MouseSpawner& spawner)
{
    while (spawner.active())
    {
        if (spawner.size() < maximumSpawnedMice())
        {
            spawner.spawn();
        }

        std::this_thread::sleep_for(spawnInterval());
    }
}

MouseSpawner::MouseSpawner(sf::RenderWindow* window) :
randomEngine(),
xDistribution(),
yDistribution(),
spawnedMice(),
timedSpawner(),
window(window),
threadActive(true),
nextId(0)
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	randomEngine.seed(seed);

	// Currently uses window size
	auto size = window->getSize();
	xDistribution = std::uniform_int_distribution<int>(0, size.x);
	yDistribution = std::uniform_int_distribution<int>(0, size.y);

	timedSpawner = std::make_unique<std::thread>(spawnTimer, std::ref(*this));
}

MouseSpawner::~MouseSpawner()
{
    threadActive = false;

    if (timedSpawner != nullptr && timedSpawner->joinable())
    {
        timedSpawner->join();
    }
}

void MouseSpawner::spawn()
{
	auto xPosition = xDistribution(randomEngine);
	auto yPosition = yDistribution(randomEngine);

	{
	    std::lock_guard<std::mutex> lock(mutex);

	    std::unique_ptr<Mouse> mouse = std::make_unique<Mouse>(nextId);

	    mouse->setBodyPosition(xPosition, yPosition);

	    spawnedMice.emplace(nextId, std::move(mouse));

	    ++nextId;
	}
}

void MouseSpawner::checkCollisions(Snake& snake)
{
	for (auto mouse = spawnedMice.begin(); mouse != spawnedMice.end(); ++mouse) {

        if(snake.checkForCollision(mouse->second->getBodyPosition(), mouse->second->getBodySize()))
        {
            std::lock_guard<std::mutex> lock(mutex);
			snake.addToSize(mousePointValue);
            mouse = spawnedMice.erase(mouse);
			if (mouse == spawnedMice.end()) {
				break;
			}
		}
    }
}

void MouseSpawner::draw() const
{
    for (auto& mouse : spawnedMice) {
        window->draw(*mouse.second);
    }
}

std::size_t MouseSpawner::size()
{
    return spawnedMice.size();
}

bool MouseSpawner::active()
{
    return threadActive;
}
