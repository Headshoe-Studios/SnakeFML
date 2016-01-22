#pragma once

#include <SFML/Graphics.hpp>

class Mouse : public sf::Drawable
{
public:
	Mouse();
	~Mouse() = default;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::CircleShape mouseBody; //just temporary - to differentiate from snake. Will perhaps just need sf::Sprite though
};

