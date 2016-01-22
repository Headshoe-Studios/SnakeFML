#include "Snake.h"


Snake::Snake()
{
	//hackity hack
	snakeBody.setSize({ 20, 20 });
}


Snake::~Snake()
{
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(snakeBody);
}