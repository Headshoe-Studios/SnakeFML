#include "Snake.hpp"

Snake::Snake(sf::RenderWindow* window) : sf::Drawable(),    
    m_direction(0.f),
    m_speed(150.f),
    m_turnSpeed(3.f),
    m_window(window)
{
	//hackity hack
    m_snakeBody.setPrimitiveType(sf::TrianglesStrip);

	///give it a starting position
	positionHistory.push_front({ 400, 400 });
	positionHistorySize = snakeOrigSize;

}

void Snake::update(float dt)
{
	//update rotation (if applicable)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_direction -= m_turnSpeed * dt;
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_direction += m_turnSpeed * dt;
	}

	//update the position
	auto xOffset = m_speed * dt * std::cos(m_direction);
	auto yOffset = m_speed * dt * std::sin(m_direction);
	auto pos = positionHistory[0] + sf::Vector2f(xOffset,yOffset);

	//check it's in the window
	auto windowRect = sf::FloatRect(0, 0, m_window->getSize().x, m_window->getSize().y);

	if (!windowRect.contains(pos))
	{
		//check where we've gone off and adjust
		while (pos.x < 0)
		{
			pos.x += windowRect.width;
		}
		while (pos.y < 0)
		{
			pos.y += windowRect.height;
		}
		while (pos.x > windowRect.width)
		{
			pos.x -= windowRect.width;
		}
		while (pos.y > windowRect.height)
		{
			pos.y -= windowRect.height;
		}
	}


	//update the history
	positionHistory.push_front(pos);
	while (positionHistory.size() >= positionHistorySize)
		positionHistory.pop_back();

    //update the vertexarray

    m_snakeBody.clear();

    static const float thickness = 5.f;

    for (std::size_t i=0; i<positionHistory.size()-1; ++i)
    {
        auto& point1 = positionHistory[i];
        auto& point2 = positionHistory[i+1];

        auto direction = point2 - point1;
        auto unitDirection = direction/std::sqrt(direction.x*direction.x+direction.y*direction.y);
        sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

        auto offset = (thickness/2.f)*unitPerpendicular;

        sf::Color color = sf::Color::White;
        if(!windowRect.contains(point1-direction) || !windowRect.contains(point2+direction))
            color = sf::Color::Transparent;

        m_snakeBody.append({point1 + offset, color});
//        m_snakeBody.append({point2 + offset, color});
//        m_snakeBody.append({point2 - offset, color});
        m_snakeBody.append({point1 - offset, color});
    }
	
	checkForTail();
}

sf::Vector2f Snake::getHeadPosition()
{
	return positionHistory[0];
}

void Snake::checkForTail()
{
	for(unsigned int i = 124; i < positionHistory.size(); ++i)
	{
		if(checkForCollision(positionHistory[i], snakeSegmentSize))
		{
			printf("touching tail at %d\n\n", i);
			positionHistorySize = snakeOrigSize;
		}
	}
}

bool Snake::checkForCollision(sf::Vector2f objPos, int objSize)
{ //using the 2 objects positions determine collison
	float a = objPos.x - getHeadPosition().x;
	float b = objPos.y - getHeadPosition().y;
	float c = sqrt(pow(a, 2) + pow(b, 2));
	if(c <= objSize)
	{
		return true;
	}
	return false;
}

void Snake::addToSize(int scoreToAdd)
{
	//increment history size for now - should ideally be more accurate
		positionHistorySize += scoreToAdd;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_snakeBody, states);
}
