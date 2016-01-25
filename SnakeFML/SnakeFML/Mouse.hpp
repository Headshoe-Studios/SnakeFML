#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <random>

class Mouse : public sf::Drawable
{
public:
	Mouse(std::uint8_t id,const sf::Texture& texture);
	~Mouse() = default;

	void setBodyPosition(float x, float y);

	sf::FloatRect getBodyRect() const;

	std::uint8_t id() const;

private:

	sf::Sprite							sprite;
	virtual void						draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//random stuff
	std::mt19937						randomEngine;
	std::uniform_int_distribution<int>	xDistribution;
	std::uniform_int_distribution<int>	yDistribution;
	std::uint8_t                        spawnId;

};

