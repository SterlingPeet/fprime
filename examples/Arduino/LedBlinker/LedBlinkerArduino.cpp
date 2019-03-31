// ====================================================================== 
// \title  LedBlinkerImpl.cpp
// \author lestarch
// \brief  cpp file for LedBlinker component implementation class
// ====================================================================== 


#include <examples/Arduino/LedBlinker/LedBlinker.hpp>
#include "Fw/Types/BasicTypes.hpp"

#include <Arduino.h>
namespace Arduino {

  void LedBlinkerComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    LedBlinkerComponentBase::init(instance);
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, HIGH);
  }

  void LedBlinkerComponentImpl ::
    blink()
  {
      digitalWrite(m_pin, m_state);
  }
} // end namespace Arduino
