#include <Watchdog.h>

void setup() {
    Serial.begin(115200);

    // Enable the watchdog. The period is set by the config bits
    // in the bootloader.
    Watchdog::enable();
    Serial.println("Watchdog enabled");
}

void loop() {
    // Keep the dog awake by kicking it
    Watchdog::kick();
    Serial.println("Watchdog kicked");
    
    // If this delay is too long the watchdog will reset
    // the board. By default most boards have the watchdog
    // timeout set to about 17 minutes.
    delay(10000);
}
