#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>

class Timer {
    private:
		//Time when the timer started
	    Uint32 startTicks;

		//Ticks stored when the timer was paused
		Uint32 pausedTicks;

		//The timer status
		bool paused;
		bool started;

		//Gets the timer's time
		Uint32 getTicks();

    public:
		Timer();

        int time;

		//Clock actions
		void start();
		void stop();
		void pause();
		void unpause();
        bool countdown(Uint32 timer);

		//Checks timer's status
		bool isStarted();
		bool isPaused();
};

#endif