#include <ATmega/examples/I2cGeneric/Top/Components.hpp>
#include <Os/Baremetal/TaskRunner/TaskRunner.hpp>
#include <Os/Task.hpp>
#ifdef ARDUINO
    #include <Os/Arduino/StreamLog.hpp>
    #include <Arduino.h>
    #include <Os/AVR/XMem.hpp>
#endif

#define STARTUP_DELAY_MS 2000

#if defined (DEBUG_TOP_FREE_RAM) || defined (DEBUG_TOP_SETUP)
  #ifdef ARDUINO
    #include <Arduino.h>
    #include <ATmega/vendor/libraries/MemoryFree/MemoryFree.h>
  #endif
  #ifndef DEBUG_Serial
    #define DEBUG_Serial Serial1
  #endif
#endif

// Baremetal setup for the task runner
Os::TaskRunner taskRunner;

/**
 * Main function.
 */
int main(int argc, char* argv[]) {
#ifdef ARDUINO
    init();
    // initVariant();  // Seems to cause main() duplicate to show up...

    DEBUG_Serial.begin(115200);
    Os::setArduinoStreamLogHandler(&DEBUG_Serial);
    DEBUG_Serial.println(F("\n\nStarted!"));
#ifdef DEBUG_TOP_FREE_RAM
  #ifdef ARDUINO
    DEBUG_Serial.print(F("\nBase Free RAM: "));
    DEBUG_Serial.println(freeMemory());
  #endif
#endif

    delay(2000);
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

// #if defined (DEBUG_TOP_FREE_RAM) || defined (DEBUG_TOP_SETUP)
//   #ifdef ARDUINO
//     DEBUG_Serial.begin(115200);
//   #endif
// #endif


    constructApp();

#ifndef ARDUINO
    printf("Starting TaskRunner.\n");
#endif

#ifdef DEBUG_TOP_FREE_RAM
  #ifdef ARDUINO
    DEBUG_Serial.print(F("\nConstructed Free RAM: "));
    DEBUG_Serial.println(freeMemory());
  #endif
#endif

    // The Baremetal taskRunner must be invoked manually
    while(1){taskRunner.run();}

    return 0;
}
