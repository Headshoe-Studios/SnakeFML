#pragma once

#include <SFML/Graphics.hpp>

class Snake : public sf::Drawable, public sf::Transformable
{
public:
	Snake();
	~Snake() = default;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray snakeBody;
};

