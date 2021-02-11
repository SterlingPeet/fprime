#ifndef __I2CGENERIC_COMPONENTS_HEADER__
#define __I2CGENERIC_COMPONENTS_HEADER__

#include <ATmega/AssertReset/AssertResetComponent.hpp>
#include <ATmega/EePrmDb/EePrmDbComponentImpl.hpp>
#include <ATmega/HardwareRateDriver/HardwareRateDriver.hpp>
#include <ATmega/examples/I2cGeneric/I2cExerciser/I2cExerciserComponent.hpp>
#include <Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>
#include <Drv/ATmegaI2cDriver/ATmegaI2cDriverComponentImpl.hpp>
#include <Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentImpl.hpp>
#include <Svc/ActiveLogger/ActiveLoggerImpl.hpp>
#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/CmdDispatcher/CommandDispatcherImpl.hpp>
#include <Svc/GroundInterface/GroundInterface.hpp>
#include <Svc/LinuxTime/LinuxTimeImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>
#include <Svc/TlmChan/TlmChanImpl.hpp>

void constructApp(void);
void constructI2cGenericArchitecture(void);
void exitTasks(void);

extern ATmega::AssertResetComponent assertResetter;
extern ATmega::EePrmDbComponentImpl eePrmDb;
extern Arduino::HardwareRateDriver hardwareRateDriver;
extern Drv::ATmegaGpioDriverComponentImpl ledGpio;
extern Drv::ATmegaI2cDriverComponentImpl i2cDriverComp;
extern Drv::ATmegaSerialDriverComponentImpl uartDriver;
extern Svc::ActiveLoggerImpl eventLogger;
extern Svc::ActiveRateGroupImpl rateGroup10HzComp;
extern Svc::CommandDispatcherImpl cmdDisp;
extern Svc::GroundInterfaceComponentImpl groundIf;
extern Svc::LinuxTimeImpl linuxTime;
extern Svc::RateGroupDriverImpl rateGroupDriverComp;
extern Svc::TlmChanImpl chanTlm;
extern examples::I2cExerciserComponent i2cExerciser;
// extern Svc::ActiveRateGroupImpl rateGroup1HzComp;

#endif  // end __I2CGENERIC_COMPONENTS_HEADER__
