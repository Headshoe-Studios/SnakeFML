#pragma once

#include <SFML\Graphics.hpp>

class Snake : public sf::Drawable
{
public:
	Snake();
	~Snake();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

private:
	sf::RectangleShape snakeBody; //will be trianglestrip or something fancier eventually
};

