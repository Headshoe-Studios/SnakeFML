#include "Mouse.hpp"
#include <chrono>
#include <functional>

Mouse::Mouse(sf::RenderWindow& window)
{
	//seed the random engine
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	randomEngine.seed(seed);

	//we want randoms from 0 - screen size
	auto size = window.getSize();
    xDistribution = std::uniform_int_distribution<int>(0, size.x);
    yDistribution = std::uniform_int_distribution<int>(0, size.y);

	//hackity hack
	mouseBody.setRadius(10);

	respawn();
}

int Mouse::getBodySize()
{
	return mouseBody.getRadius();
}

sf::Vector2f Mouse::getBodyPosition()
{
	return sf::Vector2f(mouseBody.getPosition().x+getBodySize(), mouseBody.getPosition().y+getBodySize());
}

void	Mouse::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mouseBody);
}

void	Mouse::respawn()
{
	//get a random position
	auto xPosition = xDistribution(randomEngine);
	auto yPosition = yDistribution(randomEngine);

	mouseBody.setPosition(xPosition, yPosition);
}
