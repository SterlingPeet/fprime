// ======================================================================
// \title  ATmegaGpioDriverComponentImpl.hpp
// \author Sterling Peet
// \brief  hpp file for ATmegaGpioDriver component implementation class
//
// ======================================================================

#ifndef ATmegaGpioDriver_HPP
#define ATmegaGpioDriver_HPP

#include "Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentAc.hpp"
#include <Os/Task.hpp>

namespace Drv {
  constexpr uint8_t INVALID_PIN_NUMBER = 255;

  class ATmegaGpioDriverComponentImpl :
    public ATmegaGpioDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ATmegaGpioDriver
      //!
      ATmegaGpioDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object ATmegaGpioDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ATmegaGpioDriver
      //!
      ~ATmegaGpioDriverComponentImpl(void);

      //! Start interrupt task
      // Os::Task::TaskStatus startIntTask(NATIVE_INT_TYPE priority, NATIVE_INT_TYPE cpuAffinity = -1);

      //! configure GPIO
      enum GpioDirection {
          GPIO_IN = 0, //!< input
          GPIO_OUT = 1, //!< output
          GPIO_INT //!< interrupt
      };

      //! setup GPIO
      bool setup(volatile uint8_t &data_dir_register, volatile uint8_t &port_register, int pin_number, GpioDirection direction);

      //! exit thread
      void exitThread(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for gpioRead
      //!
      void gpioRead_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          bool &state
      );

      //! Handler implementation for gpioWrite
      //!
      void gpioWrite_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          bool state
      );

      //! Data Direction Register (needs to match m_port)
      volatile uint8_t *m_ddir;

      //! Port Register (needs to match m_ddir)
      volatile uint8_t *m_port;

      //! Pin Number within Port
      uint8_t m_pin;

      // //! keep GPIO ID
      // NATIVE_INT_TYPE m_gpio;

      //! device direction
      GpioDirection m_direction;

      //! Entry point for task waiting for interrupt
      // static void intTaskEntry(void * ptr);

      //! Task object for RTI task
      // Os::Task m_intTask;
      //! file descriptor for GPIO
      // NATIVE_INT_TYPE m_fd;
      //! flag to quit thread
      // bool m_quitThread;

    };

} // end namespace Drv

#endif
