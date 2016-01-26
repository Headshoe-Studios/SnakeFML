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

	//respawn when killed
	void respawn();
	
	//check for collisions with mice
	bool checkForCollision(sf::FloatRect rect);
	void addToSize(int scoreToAdd);
	
	sf::View getView() const;

private:

	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray		m_snakeBody;

	float				m_direction;	//the current direction of the snake (in degrees)
	float				m_speed;		//current speed (in pixels/second)
	float				m_turnSpeed;	//the speed it can turn at (in degrees/second)

	sf::RenderWindow*	m_window;

	std::deque<sf::Vector2f>	positionHistory;
    std::size_t					positionHistorySize;
	
	const int snakeOrigSize = 50;
	const sf::Color			toneOne;
	const sf::Color			toneTwo;
	
	sf::View m_view;
};

