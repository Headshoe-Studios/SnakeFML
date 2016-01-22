#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class Mouse : public sf::Drawable
{
public:
	Mouse(sf::RenderWindow& window);
	~Mouse() = default;
	
	//getters for position and size
	int getBodySize();
	sf::Vector2f getBodyPosition();
	
	///Call this when you want him to respawn
	void respawn();

private:
	virtual void						draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::CircleShape						mouseBody; //just temporary - to differentiate from snake. Will perhaps just need sf::Sprite though

	//random stuff
	std::mt19937						randomEngine;
	std::uniform_int_distribution<int>	xDistribution;
	std::uniform_int_distribution<int>	yDistribution;
};

