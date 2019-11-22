#include "servo.h"
#include "mbed.h"

Servo::Servo(PinName pin_, int rotate_type_, float value, float max_pulse_ms_, float min_pulse_ms_): 
pin(pin_),
rotate_type(rotate_type_),
max_pulse_ms(max_pulse_ms_),
min_pulse_ms(min_pulse_ms_),
pwm(pin_) 
{
    if(rotate_type == LIMITED_SERVO)
    {
        range = value;
        pos = 0;
        max_speed = -1;
        speed = -1;       
    }

    else
    {
        max_speed = value;   
        speed = 0;
        range = -1;     
        pos = -1;
    }

    //INIT PWM DEFAULT
    pwm.period_ms(PERIOD);
}

Servo::Servo(PinName pin_, int rotate_type_, float value):
pin(pin_),
rotate_type(rotate_type_),
pwm(pin_)
{
    if(rotate_type == LIMITED_SERVO)
    {
        range = value;
        pos = 0;

        max_speed = -1;
        speed = -1;
    }
    else
    {
        max_speed = value;
        speed = 0;

        range = -1;
        pos = -1;
    }

    max_pulse_ms = DEFAULT_MAX;
    min_pulse_ms = DEFAULT_MIN;

    //INIT PWM DEFAULT
    pwm.period_ms(PERIOD);
}

Servo::Servo(PinName pin_, int rotate_type_):
pin(pin_),
rotate_type(rotate_type_),
pwm(pin_)
{
    if(rotate_type == LIMITED_SERVO)
    {
        range = DEFAULT_RANGE;
        pos = 0;

        max_speed = -1;
        speed = -1;
    }
    else
    {
        max_speed = 0;
        speed = 0;

        range = -1;
        pos = -1;
    }

    max_pulse_ms = DEFAULT_MAX;
    min_pulse_ms = DEFAULT_MIN;

    //INIT PWM DEFAULT
    pwm.period_ms(PERIOD);
}

bool Servo::set_range(float range_)
{
    if(rotate_type == LIMITED_SERVO)
        range = range_;
    return rotate_type == LIMITED_SERVO;
}

bool Servo::set_max_speed(float max_speed_)
{
    if(rotate_type == CONT_SERVO)
        max_speed = max_speed_;
    return rotate_type == CONT_SERVO;
}

bool Servo::set_position(float angle)
{
    if(rotate_type == LIMITED_SERVO)
    { 
        pos = angle;
        pwm.pulsewidth_ms(int((max_pulse_ms - min_pulse_ms) * angle/180 + min_pulse_ms));
    }
    else
        return false;
}

bool Servo::set_speed(float speed_)
{
    if(rotate_type == CONT_SERVO)
    {
        speed = speed_;
        pwm.pulsewidth_ms(int((max_pulse_ms-min_pulse_ms)/2 * speed/max_speed + min_pulse_ms + (max_pulse_ms-min_pulse_ms)/2));
    }
    else
        return false;
}

float Servo::read(void)
{
    if(rotate_type == LIMITED_SERVO)
        return pos;
    else
        return speed;
}

void Servo::set_period(int period)
{
    pwm.period_ms(period);
}