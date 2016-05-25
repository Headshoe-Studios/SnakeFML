#pragma once

class Options
{
public:
    Options();

    float getSnakeSpeed() const;
    bool getMovingCamera() const;

private:
    bool m_movingCamera;
    float m_snakeSpeed;
};
