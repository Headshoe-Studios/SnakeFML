#include "Mouse.hpp"

Mouse::Mouse()
{
	//hackity hack
	mouseBody.setRadius(10);
}


void Mouse::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mouseBody);
}