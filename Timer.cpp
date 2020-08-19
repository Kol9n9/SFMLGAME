#include "Timer.h"

Timer::Timer(float time,void(*timer_callback)(void *), void *object)
{
    this->time = time;
    this->currentTime = 0;
    this->timer_callback = timer_callback;
    this->isUpdate = false;
    this->object = object;
    this->isRunn = false;
    //ctor
}

Timer::~Timer()
{
    //dtor
}

void Timer::update(const float &time)
{
    if(!this->isRunn) return;
    this->currentTime += time;
    if(this->currentTime >= this->time)
    {
        this->currentTime = 0;
        this->timer_callback(this->object);
    }
}
