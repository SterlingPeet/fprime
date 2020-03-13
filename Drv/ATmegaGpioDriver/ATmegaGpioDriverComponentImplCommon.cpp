// ======================================================================
// \title  ATmegaGpioDriverImpl.cpp
// \author Sterling Peet
// \brief  cpp file for ATmegaGpioDriver component implementation class
// ======================================================================


#include <Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>
#include <Fw/Types/BasicTypes.hpp>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ATmegaGpioDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ATmegaGpioDriverComponentImpl(
        const char *const compName
    ) :
      ATmegaGpioDriverComponentBase(compName)
#else
    ATmegaGpioDriverImpl(void)
#endif
    ,m_ddir(0)   // 0 is a null pointer
    ,m_port(0)   // 0 is a null pointer
    ,m_pin(INVALID_PIN_NUMBER)  // number of left shifts for pin, 8 and up are nonsense
    // ,m_gpio(-1)
    ,m_direction(GPIO_IN)
    // ,m_fd(-1)
    // ,m_quitThread(false)
  {

  }

  void ATmegaGpioDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ATmegaGpioDriverComponentBase::init(instance);
  }

} // end namespace Drv
