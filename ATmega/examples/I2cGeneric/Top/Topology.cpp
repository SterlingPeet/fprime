#include <Components.hpp>
#include <I2cGenericSchedContexts.hpp>
#include <Fw/Logger/Logger.hpp>
#include <Fw/Types/Assert.hpp>
#include <Os/Log.hpp>
#ifdef ARDUINO
    #include <avr/io.h>
#else
    volatile uint8_t DDRB = 2;
    volatile uint8_t PORTB = 2;
    #define PB0 0
    #define PB1 1
    #define PB2 2
    #define PB3 3
    #define PB4 4
    #define PB5 5
    #define PB6 6
    #define PB7 7
#endif

// Setup the rate group driver used to drive all the ActiveRateGroups connected to it.
// For each active rate group, there is a rate divisor that represents how often it is run.
static NATIVE_INT_TYPE rate_divisors[] = {1, 10};
Svc::RateGroupDriverImpl rateGroupDriverComp("RGDRV", rate_divisors, FW_NUM_ARRAY_ELEMENTS(rate_divisors));

// Context array variables are passed to rate group members if needed to distinguish one call from another
// These context must match the rate group members connected in ArduinoTopologyAi.xml
static NATIVE_UINT_TYPE rg10HzContext[] = { I2cGeneric::CONTEXT_I2CGENERIC_10Hz, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup10HzComp("RG10Hz",rg10HzContext,FW_NUM_ARRAY_ELEMENTS(rg10HzContext));
// static NATIVE_UINT_TYPE rg1HzContext[] = {0, 0, I2cGeneric::CONTEXT_I2CGENERIC_1Hz, 0};
// Svc::ActiveRateGroupImpl rateGroup1HzComp("RG1Hz",rg1HzContext,FW_NUM_ARRAY_ELEMENTS(rg1HzContext));

// Standard system components
ATmega::AssertResetComponent assertResetter("assertResetter");
Svc::CommandDispatcherImpl cmdDisp("cmdDisp");
Svc::TlmChanImpl chanTlm("chanTlm");
Svc::ActiveLoggerImpl eventLogger("eventLogger");
ATmega::EePrmDbComponentImpl eePrmDb("eePrmDb");
Svc::GroundInterfaceComponentImpl groundIf("groundIf");
Drv::ATmegaSerialDriverComponentImpl uartDriver("uartDriver");
Svc::LinuxTimeImpl linuxTime("linuxTime");

// Arduino specific components
examples::I2cExerciserComponent i2cExerciser("i2cExerciser");
Arduino::HardwareRateDriver hardwareRateDriver("RateDr", 100);
Drv::ATmegaGpioDriverComponentImpl ledGpio("ledGpio");
Drv::ATmegaI2cDriverComponentImpl i2cDriverComp("i2cDr");

/**
 * Construct App:
 *
 * Constructs the App. It initialize components, call for command registration and
 * starts tasks. This is the initialization of the application, so new tasks and
 * memory can be acquired here, but should not be created at a later point.
 */
void constructApp(void) {

    // Initialize each component instance in memory
    uartDriver.init(0);

    rateGroupDriverComp.init();

    rateGroup10HzComp.init(10, 0);
    // rateGroup1HzComp.init(10, 1);

    eePrmDb.init(0, 32, 1024);

    eventLogger.init(5,0);

    // linuxTime.init(0);

    cmdDisp.init(1,0);

    chanTlm.init(2,0);

    groundIf.init(0);

    i2cExerciser.init(0);

    ledGpio.init(0);

    i2cDriverComp.init(0);

#ifndef ARDUINO
    printf("Constructing Architecture.\n");
#endif
    // Callback to initialize architecture, connect ports, etc.
    // The contents of the function are autocoded from the
    // I2cGenericTopologyAppAi.xml, and
    // incorporates the assembly name.
    constructI2cGenericArchitecture();

    /* Register commands */
    eventLogger.regCommands();
    cmdDisp.regCommands();
    eePrmDb.regCommands();
    i2cExerciser.regCommands();

    // read parameters
    i2cExerciser.loadParameters();

    // configure things
    uartDriver.open(Drv::ATmegaSerialDriverComponentImpl::DEVICE::USART0,
                    Drv::ATmegaSerialDriverComponentImpl::BAUD_RATE::BAUD_115K,
                    Drv::ATmegaSerialDriverComponentImpl::PARITY::PARITY_NONE);
    ledGpio.setup(DDRB, PORTB, PB5, Drv::ATmegaGpioDriverComponentImpl::GPIO_OUT);

    // Start all active components' tasks thus finishing the setup portion of this code
    hardwareRateDriver.start();
    rateGroup10HzComp.start(0, 120, 10 * 1024);
    // rateGroup1HzComp.start(0, 119, 10 * 1024);
    cmdDisp.start(0,101,10*1024);
    eventLogger.start(0,98,10*1024);
    chanTlm.start(0,97,10*1024);
}

/**
 * Exit Tasks:
 *
 * Exits the tasks in preparation for stopping the software. This is likely
 * not needed for Arduino projects, as they run forever, however; it is here
 * for completeness.
 */
void exitTasks(void) {
    // rateGroup1HzComp.exit();
    rateGroup10HzComp.exit();
    eventLogger.exit();
    chanTlm.exit();
}
