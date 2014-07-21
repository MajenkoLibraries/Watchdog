Watchdog
========

Manage the PIC32 watchdog timer, and activate sleep or idle modes, waking up using the watchdog.

**NOTE:** The sleep / idle functionality, using the watchdog to wake up, requires a bootloader with NMI
support.  This support is in the current chipKIT bootloader github repository so you will have to build
your own bootloader image to use it.
