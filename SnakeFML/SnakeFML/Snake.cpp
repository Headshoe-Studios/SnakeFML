#include "Snake.hpp"

Snake::Snake() : sf::Drawable()
{
    snakeBody.setPrimitiveType(sf::TrianglesStrip);
    snakeBody.append({{0, 0}});
    snakeBody.append({{0, 20}});
    snakeBody.append({{20, 0}});
    snakeBody.append({{20, 20}});
	setPosition(400, 400);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
	target.draw(snakeBody, states);
}
