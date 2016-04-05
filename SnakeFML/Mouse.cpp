#include "Mouse.hpp"
#include <chrono>
#include <functional>

Mouse::Mouse(std::uint8_t id, const sf::Texture& texture) :	
	sprite(texture),
	spawnId(id)
{
}

void Mouse::setBodyPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

sf::FloatRect Mouse::getBodyRect() const
{
	return sprite.getGlobalBounds();
}

void Mouse::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

std::uint8_t Mouse::id() const
{
    return spawnId;
}
