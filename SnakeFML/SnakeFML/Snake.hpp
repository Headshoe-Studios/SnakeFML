#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include <random>

class Snake : public sf::Drawable, public sf::Transformable
{
public:
	Snake(sf::RenderWindow* window, std::string headTexture);
	~Snake() = default;

	//update the sssssnake
	void update(float dt);

	//respawn when killed
	void respawn();
	
	//check for collisions with mice
	bool checkForCollision(sf::FloatRect rect);
	void addToSize(int scoreToAdd);
	
	sf::View getView() const;

private:

	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray		m_snakeBody;
	float				tailLength;		//the fraction of the snake to make the tail

	float				m_direction;	//the current direction of the snake (in degrees)
	float				m_speed;		//current speed (in pixels/second)
	float				m_turnSpeed;	//the speed it can turn at (in degrees/second)


	sf::RenderWindow*	m_window;

	std::deque<sf::Vector2f>	positionHistory;
    std::size_t					positionHistorySize;
	
	const int snakeOrigSize = 50;
	sf::Color					toneOne;
	sf::Color					toneTwo;
	
	sf::Texture					m_headTexture;
	sf::Sprite					m_headSprite;

	std::mt19937                             randomEngine;
	std::uniform_int_distribution<int>       colourDistribution;	//for getting random colours!
	
	sf::View m_view;
};

