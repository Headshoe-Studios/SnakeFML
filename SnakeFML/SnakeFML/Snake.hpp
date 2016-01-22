#pragma once

#include <SFML/Graphics.hpp>

class Snake : public sf::Drawable
{
public:
	Snake();
	~Snake() = default;

private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RectangleShape snakeBody; //will be trianglestrip or something fancier eventually
};

