#include <Watchdog.h>

void Watchdog::enable() {
	WDTCONbits.ON = 1;
}

void Watchdog::disable() {
	WDTCONbits.ON = 0;
}

void Watchdog::kick() {
#ifdef __PIC32MZ__
    WDTCONbits.WDTCLRKEY = 0x5743;
#else
	WDTCONbits.WDTCLR = 1;
#endif
}

void Watchdog::enableSleepMode() {
	// Standard unlock sequence
	SYSKEY = 0x0;
	SYSKEY = 0xAA996655;
	SYSKEY = 0x556699AA;
	OSCCONSET = 0x10; // Enable sleep mode
	SYSKEY = 0x0;
}

void Watchdog::enableIdleMode() {
	// Standard unlock sequence
	SYSKEY = 0x0;
	SYSKEY = 0xAA996655;
	SYSKEY = 0x556699AA;
	OSCCONCLR = 0x10; // Disable sleep mode
	SYSKEY = 0x0;
}

void __attribute__((nomips16)) Watchdog::wait() {
	kick();
	uint32_t i = disableInterrupts(); // We don't want any old interrupt waking us up
    asm volatile("mfc0 $26, $12");
    asm volatile("ins $26, $0, 10, 3");
    asm volatile("mtc0 $26, $12");
	asm volatile("wait");
	restoreInterrupts(i);
}

void Watchdog::sleep() {
	enableSleepMode();
	enable();
	kick();
	wait();
	disable();
	enableIdleMode();
}

void Watchdog::idle() {
	enableIdleMode();
	enable();
	kick();
	wait();
	disable();
}
