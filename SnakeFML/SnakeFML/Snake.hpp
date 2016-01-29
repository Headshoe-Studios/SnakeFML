#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include <random>
#include "World.h"
#include "Score.hpp"

class Snake : public sf::Drawable, public sf::Transformable
{
public:
	Snake(sf::RenderWindow& window, World& world, Score& score, std::string headTexture);
	~Snake() = default;

	//update the sssssnake
	void update(float dt);

	//respawn when killed
	void respawn();
	
	//check for collisions with mice
	bool checkForCollision(sf::FloatRect rect);
	void addToSize(int scoreToAdd);
	
	//get current size - original size to be used as score
	int getCurrentScore();
	
	sf::View getView() const;

private:

	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray		m_snakeBody;
	float				tailLength;		//the fraction of the snake to make the tail

	float				m_direction;	//the current direction of the snake 
	float				m_speed;		//current speed 
	float				m_turnSpeed;	//the speed it can turn at 

	sf::RenderWindow*	m_window;
	World*				m_world;
	Score*				m_score;

	std::deque<sf::Vector2f>	positionHistory;
    std::size_t					positionHistorySize;
	
	const int snakeOrigSize = 50;
	sf::Color					toneOne;
	sf::Color					toneTwo;
	
	sf::Texture					m_headTexture;
	sf::Sprite					m_headSprite;

	std::mt19937                             randomEngine;
	std::uniform_int_distribution<int>       colourDistribution;	//for getting random colours!

	sf::View								m_view;
	float									lifeSpan;
};

