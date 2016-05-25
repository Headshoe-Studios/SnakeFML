#pragma once

class Options
{
public:
    Options();

    float getSnakeSpeed() const;

private:
    bool m_movingCamera;
    float m_snakeSpeed;
};
