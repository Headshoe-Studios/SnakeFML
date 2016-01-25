#include "Snake.hpp"

Snake::Snake(sf::RenderWindow* window) : sf::Drawable(),
m_direction(0.f),
m_speed(150.f),
m_turnSpeed(3.f),
m_window(window),
toneOne(sf::Color::Yellow),
toneTwo(sf::Color::Blue)
{
    m_snakeBody.setPrimitiveType(sf::TrianglesStrip);
	respawn();
}

void Snake::update(float dt)
{
	//update rotation (if applicable)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_direction -= m_turnSpeed * dt;
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
		//dead
		respawn();
		return;
	}


	//update the history
	positionHistory.push_front(pos);
	while (positionHistory.size() >= positionHistorySize)
		positionHistory.pop_back();

    //update the vertexarray

    m_snakeBody.clear();

    static const float thickness = 15.f;

	for (std::size_t i = 0; i < positionHistory.size() - 1; ++i)
	{
		auto& point1 = positionHistory[i];
		auto& point2 = positionHistory[i + 1];

		auto direction = point2 - point1;
		auto unitDirection = direction / std::sqrt(direction.x*direction.x + direction.y*direction.y);
		sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

		auto offset = (thickness / 2.f)*unitPerpendicular;

		//just give it a funky colour for now...
		m_snakeBody.append({ point1 + offset, (i % 3) ? toneOne : toneTwo });
		m_snakeBody.append({ point1 - offset, (i % 4) ? toneOne : toneTwo });

		//check we don't go off the end of the array
		if (i > 2)
		{
			auto p1(m_snakeBody[m_snakeBody.getVertexCount()-1].position);
			auto p2(m_snakeBody[m_snakeBody.getVertexCount() - 2].position);
			auto p3(m_snakeBody[m_snakeBody.getVertexCount() - 3].position);
			//barycentric co-ordinate magic (possibly a bit of copypasta
			auto barycentric = [&](sf::Vector2f snakeHead)
			{
				float alpha = ((p2.y - p3.y)*(snakeHead.x - p3.x) + (p3.x - p2.x)*(snakeHead.y - p3.y)) /
					((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));
				float beta = ((p3.y - p1.y)*(snakeHead.x - p3.x) + (p1.x - p3.x)*(snakeHead.y - p3.y)) /
					((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));
				float gamma = 1.0f - alpha - beta;

				return (alpha > 0 && beta > 0 && gamma > 0);
			};
			//check front two corners
			if (barycentric(positionHistory[0]) || barycentric(positionHistory[1]))
			{
				respawn();
			}
		}
    }
}


bool Snake::checkForCollision(sf::FloatRect rect)
{ 
	//check the rect doesn't contain any of our points
	for (size_t i = 0; i < m_snakeBody.getVertexCount(); i++)
	{
		if (rect.contains(m_snakeBody[i].position))
			return true;
	}
	return false;
}

void	Snake::respawn()
{
	positionHistorySize = snakeOrigSize;
	positionHistory.clear();
	sf::Vector2f windowSize(m_window->getSize());
	positionHistory.push_front({ windowSize.x / 2,windowSize.y / 2 });
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
