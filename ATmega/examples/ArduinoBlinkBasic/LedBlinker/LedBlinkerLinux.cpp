// ======================================================================
// \title  LedBlinkerImpl.cpp
// \author lestarch
// \brief  cpp file for LedBlinker component implementation class
// ======================================================================


#include <ATmega/examples/ArduinoBlinkBasic/LedBlinker/LedBlinker.hpp>
#include "Fw/Types/BasicTypes.hpp"

#include <stdio.h>

namespace Arduino {
  void LedBlinkerComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    LedBlinkerComponentBase::init(instance);
  }

  void LedBlinkerComponentImpl ::
    blink()
  {
      static U64 s_counter = 0;
      if ((s_counter % 10) == 0) {
          printf("Setting: gpio to %d\n", m_state);
      }
      if ((s_counter % 10) == 5) {
          printf("Setting: gpio to %d\n", m_state);
      }
      s_counter += 1;
  }
} // end namespace Arduino
