#include <Fw/Types/BasicTypes.hpp>
// #include <Fw/Types/Assert.hpp>
#include <Atmega/ArduinoBlinkBasic/HardwareRateDriver/HardwareRateDriver.hpp>

namespace Arduino {

HardwareRateDriver* HardwareRateDriver::s_driver = NULL;

#if FW_OBJECT_NAMES == 1
    HardwareRateDriver::HardwareRateDriver(const char* compName, U32 intervalMs) :
        HardwareRateDriverComponentBase(compName),
#else
    HardwareRateDriver::HardwareRateDriver(U32 intervalMs),
#endif
        m_interval(intervalMs)
    {
        s_driver = this;
    }

    HardwareRateDriver::~HardwareRateDriver(void) {}

    void HardwareRateDriver::s_timer(void* comp) {
        Svc::TimerVal now;
        now.take();
        HardwareRateDriver* driver = reinterpret_cast<HardwareRateDriver*>(comp);
        //Check if it is time to run the group
        driver->CycleOut_out(0, now);
        driver->m_last = now;
    }
}
