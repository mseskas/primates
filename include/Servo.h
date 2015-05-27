#ifndef servo_H
#define servo_H

#include <PwmChip.h>

#include <project_constants.h>
#include <iostream>

using namespace std;

class servo
{
public:
    ~servo();
    servo(pwm_chip * chip, int pin_no);
    void set_angle(float new_angle);
    float get_angle();
    void turn(float angle);
    int _max_ticks;
    int _min_ticks;

    void Reset();

protected:
private:
    pwm_chip * _chip_PCA9685;
    int _pin;
    float _angle;

};

#endif // servo_H
