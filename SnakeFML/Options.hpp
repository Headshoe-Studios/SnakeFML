#pragma once

class Options
{
public:
    Options();

    bool getMovingCamera() const;
    void setMovingCamera(bool movingCamera);

private:
    bool m_movingCamera;
};
