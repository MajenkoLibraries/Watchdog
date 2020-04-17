#ifndef _WATCHDOG_H
#define _WATCHDOG_H

#if (ARDUINO >= 100)
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

class Watchdog {
	public:
		static void enable();
		static void disable();
		static void kick();
		static void enableSleepMode();
		static void enableIdleMode();
        static void __attribute__((nomips16)) wait();

		static void sleep();
		static void idle();
};

#endif
