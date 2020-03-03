/*
 * ArduinoTimeImpl.cpp:
 *
 * An implementation of LinuxTime used on the AVR platform so that
 * standard system components can be run as expected. The time format is
 * (U32 seconds, U32 microseconds).
 *
 * @author Sterling Peet
 */

#include <Svc/LinuxTime/LinuxTimeImpl.hpp>
#include <Fw/Time/Time.hpp>

namespace Svc {

#if FW_OBJECT_NAMES == 1
    LinuxTimeImpl::LinuxTimeImpl(const char* name) : TimeComponentBase(name)
#else
    LinuxTimeImpl::LinuxTimeImpl()
#endif
    {}

    LinuxTimeImpl::~LinuxTimeImpl() {}

    void LinuxTimeImpl::timeGetPort_handler(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::Time &time /*!< The time to set */
    ) {
        U32 msec = 0; //millis();
        U32 usec = 0; //micros();
        time.set(msec/1000, usec);
    }

    void LinuxTimeImpl::init(NATIVE_INT_TYPE instance) {
        TimeComponentBase::init(instance);
    }
}
