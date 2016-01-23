#pragma once

#include <SFML/Graphics.hpp>
#include <deque>

class Snake : public sf::Drawable, public sf::Transformable
{
public:
	Snake(sf::RenderWindow* window);
	~Snake() = default;

	//update the sssssnake
	void update(float dt);
	
	//get head position
	sf::Vector2f getHeadPosition();
	
	//check for collisions with mice
	bool checkForCollision(sf::Vector2f objPos, int objSize);	

private:

	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray		m_snakeBody;	//will be trianglestrip or something fancier eventually

	float				m_direction;	//the current direction of the snake (in degrees)
	float				m_speed;		//current speed (in pixels/second)
	float				m_turnSpeed;	//the speed it can turn at (in degrees/second)

	sf::RenderWindow*	m_window;

	std::deque<sf::Vector2f>	positionHistory;
	int							positionHistorySize;
};

