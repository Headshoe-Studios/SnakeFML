#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <random>

class Mouse : public sf::Drawable
{
public:
	Mouse(std::uint8_t id);
	~Mouse() = default;

	void setBodyPosition(float x, float y);

	//getters for position and size
	int getBodySize() const;
	sf::Vector2f getBodyPosition() const;

	std::uint8_t id() const;

private:
	virtual void						draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::CircleShape						mouseBody; //just temporary - to differentiate from snake. Will perhaps just need sf::Sprite though

	//random stuff
	std::mt19937						randomEngine;
	std::uniform_int_distribution<int>	xDistribution;
	std::uniform_int_distribution<int>	yDistribution;
	std::uint8_t                        spawnId;
};

