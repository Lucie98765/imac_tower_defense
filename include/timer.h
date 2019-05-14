#ifndef TIMER_H
#define TIMER_H

#include "headers.h"
	
class Timer
{

    private:
		float startTicks;
        float nextTicks;
		float pauseTicks;

		bool	paused;
		bool	started;


	public:
		//constructor
		Timer();

		//destructor
		~Timer();

		//methods
		void start();
		void pause();
		void unpause();
		void stop();

		//getters
		float	get_Ticks(int n);
		bool	pause_activate();
		bool	start_activate();

        //setters
        void set_startTicks(float newvalue);
        void set_nextTicks(float newvalue);
        void set_pauseTicks(float newvalue);
};

#endif /* !TIMER_H */