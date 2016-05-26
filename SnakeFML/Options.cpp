#include "Options.hpp"

Options::Options():
    m_movingCamera(true)
{

}

bool Options::getMovingCamera() const
{
    return m_movingCamera;
}

void Options::setMovingCamera(bool movingCamera)
{
    m_movingCamera = movingCamera;
}
