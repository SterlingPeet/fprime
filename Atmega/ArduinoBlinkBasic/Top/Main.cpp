#include <Atmega/ArduinoBlinkBasic/Top/Components.hpp>
#ifdef ARDUINO
    #include <Os/Arduino/StreamLog.hpp>
    #include <Arduino.h>
#else
    #include <examples/ArduinoGpsTracker/SerialDriver/SerialDriver.hpp>
#endif

#define STARTUP_DELAY_MS 2000

/**
 * Main function.
 */
int main(int argc, char* argv[]) {
    init();
    // initVariant();  // Seems to cause main() duplicate to show up...
#ifdef ARDUINO
    delay(STARTUP_DELAY_MS);
    // Two quick flashes for viz indication
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(600);
#endif
    constructApp();
#ifndef ARDUINO
    while (1) {}
#endif
    return 0;
}
