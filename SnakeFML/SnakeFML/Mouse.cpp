#include "Mouse.hpp"
#include <chrono>
#include <functional>

Mouse::Mouse(std::uint8_t id) :
spawnId(id)
{
	//hackity hack
	mouseBody.setRadius(10);
}

void Mouse::setBodyPosition(float x, float y)
{
    mouseBody.setPosition(x, y);
}

int Mouse::getBodySize() const
{
	return mouseBody.getRadius();
}

sf::Vector2f Mouse::getBodyPosition() const
{
	return sf::Vector2f(mouseBody.getPosition().x + getBodySize(), mouseBody.getPosition().y + getBodySize());
}

void Mouse::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mouseBody);
}

std::uint8_t Mouse::id() const
{
    return spawnId;
}
