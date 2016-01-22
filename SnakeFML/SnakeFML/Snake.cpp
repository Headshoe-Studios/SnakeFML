#include "Snake.hpp"


Snake::Snake() : sf::Drawable()
{
	//hackity hack
	snakeBody.setSize({ 20, 20 });
	snakeBody.setPosition(400, 400);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(snakeBody);
}