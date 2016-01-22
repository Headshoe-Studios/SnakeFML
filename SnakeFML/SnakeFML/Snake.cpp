#include "Snake.hpp"

Snake::Snake(sf::RenderWindow* window) : sf::Drawable(),
    m_speed(150.f),
    m_direction(0.f),
    m_turnSpeed(3.f),
    m_window(window),
    turningLeft(false),
    turningRight(false)
{
	//hackity hack
    m_snakeBody.setPrimitiveType(sf::TrianglesStrip);

	///give it a starting position
	positionHistory.push_front({ 400, 400 });
	positionHistorySize = 50;

}

void Snake::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
            turningLeft = true;
            break;
        case sf::Keyboard::Right:
            turningRight = true;
            break;
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
            turningLeft = false;
            break;
        case sf::Keyboard::Right:
            turningRight = false;
            break;
        }
    }
}

void Snake::update(float dt)
{
	//update rotation (if applicable)
	if (turningLeft)
	{
		m_direction -= m_turnSpeed * dt;
	}
	if (turningRight)
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

    static const float thickness = 100.f;

    for (std::size_t i=0; i<positionHistory.size()-1; ++i)
    {
        sf::Vector2f& point1 = positionHistory[i];
        sf::Vector2f& point2 = positionHistory[i+1];

        sf::Vector2f direction = point2 - point1;
        sf::Vector2f unitDirection = direction/std::sqrt(direction.x*direction.x+direction.y*direction.y);
        sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

        sf::Vector2f offset = (thickness/2.f)*unitPerpendicular;

        m_snakeBody.append(point1 + offset);
//        m_snakeBody.append(point2 + offset);
//        m_snakeBody.append(point2 - offset);
        m_snakeBody.append(point1 - offset);
    }
}

sf::Vector2f Snake::getHeadPosition()
{
	return positionHistory[0];
}

bool Snake::checkForCollision(sf::Vector2f objPos, int objSize)
{ //using the 2 objects positions determine collison
	float a = objPos.x - getHeadPosition().x;
	float b = objPos.y - getHeadPosition().y;
	float c = sqrt(pow(a, 2) + pow(b, 2));
	if(c <= objSize){
		return true;
	}
	return false;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_snakeBody, states);
}
