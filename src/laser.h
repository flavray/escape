#ifndef __LASER_H__
#define __LASER_H__

class Laser {
public:
    Laser();
    void update(float y);

    float y() { return _y; }

    static constexpr const float SPEED = 0.009f;

private:
    float _y;
};

#endif
