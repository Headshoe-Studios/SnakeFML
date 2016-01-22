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
    m_snakeBody.append({{0, 0}});
    m_snakeBody.append({{0, 20}});
    m_snakeBody.append({{20, 0}});
    m_snakeBody.append({{20, 20}});
    setPosition(400, 400);
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
    //update the position
    auto xOffset = m_speed * dt * std::cos(m_direction);
    auto yOffset = m_speed * dt * std::sin(m_direction);
    auto pos = getPosition() + sf::Vector2f(xOffset,yOffset);

    //update rotation (if applicable)
    if (turningLeft)
    {
        m_direction -= m_turnSpeed * dt;
    }
    if (turningRight)
    {
        m_direction += m_turnSpeed * dt;
    }

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
    setPosition(pos);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_snakeBody, states);
}
