#ifndef TIMER_H
#define TIMER_H


class Timer
{
    public:
        Timer(float time,void(*timer_callback)(void *),void *object);
        virtual ~Timer();
        void update(const float &time);
        void start(){isRunn = true;}
        void stop(){isRunn = false;}
        void restart(){isRunn = true; currentTime = 0;}
        bool const &isRun() {return isRunn;}
    protected:

    private:
        void (*timer_callback)(void *);
        void *object;
        bool isUpdate;
        float time;
        float currentTime;
        bool isRunn;
};

#endif // TIMER_H
