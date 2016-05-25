#include "Options.hpp"

Options::Options():
    m_movingCamera(true),
    m_snakeSpeed(150.f)
{

}

float Options::getSnakeSpeed() const
{
    return m_snakeSpeed;
}
