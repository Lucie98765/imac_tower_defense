#include "../include/timer.h"

// constructor
    Timer::Timer()
    {
        startTicks = 0;
        nextTicks = 0;
        pauseTicks = 0;
        paused = false;
        started = false;
    }
    
//destructor
    Timer::~Timer() {}

//methods
    void Timer::start()
    {
        started = true;
        paused = false;
        
        startTicks = SDL_GetTicks();
    }


    void Timer::pause()
    {
        if (started && !paused)
        {
            paused = true;

            pauseTicks = SDL_GetTicks() - startTicks;
        }
    }


    void Timer::unpause()
    {
        if (paused)
        {
            paused = false;
            
            startTicks = SDL_GetTicks() - pauseTicks;
            pauseTicks = 0;
        }
    }


    void Timer::stop()
    {
        started = false;
        paused = false;
    }

//getters

    float Timer::get_Ticks(int n)
    {
        if (n == 0) {
            return startTicks;
        }
        else if (n==1) {
            return nextTicks;
        }
        else {
            return pauseTicks;
        }
    }


    bool Timer::pause_activate()
    {
        return paused;
    }


    bool Timer::start_activate()
    {
        return started;
    }

//setters

    void Timer::set_startTicks(float newvalue)
    {
        startTicks = newvalue;
    }

    void Timer::set_nextTicks(float newvalue)
    {
        nextTicks = newvalue;
    }

    void Timer::set_pauseTicks(float newvalue)
    {
        pauseTicks = newvalue;
    }
