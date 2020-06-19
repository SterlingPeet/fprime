#include <ATmega/AssertReset/AssertResetComponent.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Types/Assert.hpp>
#include <Fw/Log/LogString.hpp>
#include <Fw/Logger/Logger.hpp>
#include <stdio.h>
#include <Arduino.h>
#include <avr/wdt.h>

#define SERIAL_PORT Serial
#define FATAL_BAUD 115200


namespace ATmega {
  volatile U32 assertFlag __attribute__ ((section(".noinit")));
  volatile FILE_NAME_ARG prevAssertFile __attribute__ ((section(".noinit")));
  volatile NATIVE_UINT_TYPE prevAssertLineNo __attribute__ ((section(".noinit")));
  volatile NATIVE_UINT_TYPE prevAssertNumArgs __attribute__ ((section(".noinit")));
  volatile AssertArg prevAssertArg1 __attribute__ ((section(".noinit")));
  volatile AssertArg prevAssertArg2 __attribute__ ((section(".noinit")));
  volatile AssertArg prevAssertArg3 __attribute__ ((section(".noinit")));
  volatile AssertArg prevAssertArg4 __attribute__ ((section(".noinit")));
  volatile AssertArg prevAssertArg5 __attribute__ ((section(".noinit")));
  volatile AssertArg prevAssertArg6 __attribute__ ((section(".noinit")));

  void AssertResetComponent::AssertReset::doAssert(void) {
        // for **duino, delay then let WD expire to reset processor
        Fw::Logger::logMsg("A FATAL Assert Occurred.\n",0,0,0,0,0,0);
        SERIAL_PORT.println("A FATAL Assert Occurred.");
        // (void)Os::Task::delay(1000);
        Fw::Logger::logMsg("Resetting.\n",0,0,0,0,0,0);
        SERIAL_PORT.println("Resetting.");

        //  Sometimes this doesn't act correctly if it is not
        //  cleared before the watchdog reset ?!?
        MCUCSR = 0;
        // https://www.nongnu.org/avr-libc/user-manual/group__avr__watchdog.html
        wdt_enable(WDTO_500MS);
        while(1);
  }

  void AssertResetComponent::reportAssert(
          FILE_NAME_ARG file,
          NATIVE_UINT_TYPE lineNo,
          NATIVE_UINT_TYPE numArgs,
          AssertArg arg1,
          AssertArg arg2,
          AssertArg arg3,
          AssertArg arg4,
          AssertArg arg5,
          AssertArg arg6
          ) {

      assertFlag = assertFlagTrue;
      prevAssertFile = file;
      prevAssertLineNo = lineNo;
      prevAssertNumArgs = numArgs;
      prevAssertArg1 = arg1;
      prevAssertArg2 = arg2;
      prevAssertArg3 = arg3;
      prevAssertArg4 = arg4;
      prevAssertArg5 = arg5;
      prevAssertArg6 = arg6;

#if FW_ASSERT_LEVEL == FW_FILEID_ASSERT
      Fw::LogStringArg fileArg;
      fileArg.format("0x%08X",file);
#else
      Fw::LogStringArg fileArg((const char*)file);
#endif

      I8 msg[FW_ASSERT_TEXT_SIZE];
      Fw::defaultReportAssert(file,lineNo,numArgs,arg1,arg2,arg3,arg4,arg5,arg6,msg,sizeof(msg));
      SERIAL_PORT.begin(FATAL_BAUD);
      SERIAL_PORT.println();
      SERIAL_PORT.print((const char*)msg);
      delay(1000);
  }

} // end namespace ATmega
