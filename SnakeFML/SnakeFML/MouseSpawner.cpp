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

MouseSpawner::MouseSpawner(sf::RenderWindow* window, std::string mouseTexture, Snake& snake) :
	randomEngine(),
	xDistribution(),
	yDistribution(),
	spawnedMice(),
	spawnTimer(),
	window(window),
	nextId(0),
	m_snake(&snake),
	active(true)
{
	m_mouseTexture.loadFromFile(mouseTexture);

	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	randomEngine.seed(static_cast<int>(seed));

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
			std::unique_ptr<Mouse> mouse = std::make_unique<Mouse>(nextId, m_mouseTexture);

			sf::FloatRect windowRect(0, 0, static_cast<float>(window->getSize().x-m_mouseTexture.getSize().x), static_cast<float>(window->getSize().y - m_mouseTexture.getSize().y));
			bool success;
			do
			{
				success = true;

				//get random spawn position
				auto xPosition = xDistribution(randomEngine);
				auto yPosition = yDistribution(randomEngine);
				mouse->setBodyPosition(static_cast<float>(xPosition), static_cast<float>(yPosition));

				if (m_snake->checkForCollision(mouse->getBodyRect())) //check it doesn't collide with the snake
				{
					success = false;
				}
				else if (!windowRect.contains({ mouse->getBodyRect().left,mouse->getBodyRect().top }))	// check it's in the window
				{
					success = false;
				}
				else
				{
					//check the rest of the mice for collisions
					for (auto& otherMouse : spawnedMice)
					{
						if (mouse->getBodyRect().intersects(otherMouse.second->getBodyRect()))
						{
							success = false;
							break;
						}
					}
				}
			} while (!success);
     
            spawnedMice.emplace(nextId, std::move(mouse));

            ++nextId;
	    }
	}
}

void MouseSpawner::checkCollisions()
{
	for (auto mouse = spawnedMice.begin(); mouse != spawnedMice.end(); ++mouse)
	{
        if(m_snake->checkForCollision(mouse->second->getBodyRect()))
        {
			m_snake->addToSize(mousePointValue);
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
