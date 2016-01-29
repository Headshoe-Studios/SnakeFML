#define _USE_MATH_DEFINES
#include "Snake.hpp"
#include <cmath>
#include <chrono>

Snake::Snake(sf::RenderWindow& window, World& world, Score& score, std::string headTexture) : sf::Drawable(),
tailLength(0.2f),
m_direction(0.f),
m_speed(150.f),
m_turnSpeed(3.f),
m_window(&window),
m_world(&world),
m_score(&score),
m_view(m_window->getDefaultView())
{
	//load the head
	m_headTexture.loadFromFile(headTexture);
	m_headSprite.setTexture(m_headTexture, true);

	//set origin to center
	auto headRect(m_headSprite.getGlobalBounds());
	m_headSprite.setOrigin(headRect.width / 2, headRect.height / 2);

	//pick two random body colours
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	randomEngine.seed(seed);
	colourDistribution = std::uniform_int_distribution<int>(0, sf::Color::White.r);

	auto rnd = [&]
	{
		return colourDistribution(randomEngine);
	};

	toneOne = sf::Color(rnd(), rnd(), rnd());
	toneTwo = sf::Color(rnd(), rnd(), rnd());

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
		m_view.rotate(-m_turnSpeed * dt * 180/M_PI);		
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_direction += m_turnSpeed * dt;
		m_view.rotate(m_turnSpeed * dt * 180/M_PI);
	}

	//update the position
	auto xOffset = m_speed * dt * std::cos(m_direction);
	auto yOffset = m_speed * dt * std::sin(m_direction);
	auto pos = positionHistory[0] + sf::Vector2f(xOffset,yOffset);

	//check we haven't departed this world
	if (!m_world->getBounds().contains(pos))
	{
		respawn();
		return;
	}

	//update the history
	positionHistory.push_front(pos);
	while (positionHistory.size() > positionHistorySize)
		positionHistory.pop_back();

	//update the head sprite
	m_headSprite.setPosition(positionHistory[0]);
	m_headSprite.setRotation(m_direction * 180 / M_PI);

	//and the view
	m_view.setCenter(positionHistory.front());

    //update the vertexarray
    m_snakeBody.clear();

    static const float bodyThickness = 15.f;

	for (std::size_t i = 0; i < positionHistory.size() - 1; ++i)
	{
		auto& point1 = positionHistory[i];
		auto& point2 = positionHistory[i + 1];

		auto direction = point2 - point1;
		auto unitDirection = direction / std::sqrt(direction.x*direction.x + direction.y*direction.y);
		sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

		auto thisThickness(bodyThickness);
		//check if we're part of the tail
		auto countToEnd(positionHistory.size() - i);
		auto tailCount(positionHistory.size()*tailLength);
		if (countToEnd < tailCount )
		{
			//adjust the thickness based on our distance from the end
			thisThickness *= countToEnd / tailCount;
		}
		auto offset = (thisThickness / 2.f)*unitPerpendicular;

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
				return;
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
	auto worldBounds(m_world->getBounds());
	positionHistory.push_front({ worldBounds.width / 2,worldBounds.height / 2 });
	m_direction = 0;
	
	m_view.setRotation(90-m_direction*180/M_PI);
	m_view.setCenter(positionHistory.front());
	m_score->update(positionHistory.size());
}

void Snake::addToSize(int scoreToAdd)
{
	//increment history size for now - should ideally be more accurate
	positionHistorySize += scoreToAdd;
	m_score->update(positionHistory.size());
}

int Snake::getCurrentScore()
{
	return positionHistorySize - snakeOrigSize;
}

sf::View Snake::getView() const
{
	return m_view;	
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_snakeBody, states);
	target.draw(m_headSprite, states);
}
