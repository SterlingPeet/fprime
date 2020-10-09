// ======================================================================
// \title  ATmegaI2cDriverComponentImpl.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  I2C driver for operating the I2C bus on an ATmega hardware platform (such as ATmega128).
// ======================================================================


#include "Drv/ATmegaI2cDriver/ATmegaI2cDriverComponentImpl.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ATmegaI2cDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ATmegaI2cDriverComponentImpl(
        const char *const compName
    ) :
      ATmegaI2cDriverComponentBase(compName),
#else
    ATmegaI2cDriverComponentImpl(void) :
#endif
     m_freq(0)
    ,m_timeout(5000)
  {

  }

  void ATmegaI2cDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ATmegaI2cDriverComponentBase::init(instance);
    m_timer = Os::IntervalTimer();
  }

  void ATmegaI2cDriverComponentImpl ::
    setTimeout(NATIVE_UINT_TYPE timeout)
  {
    m_timeout = timeout;
  }

  ATmegaI2cDriverComponentImpl ::
    ~ATmegaI2cDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  Drv::I2cStatus ATmegaI2cDriverComponentImpl ::
    i2cTransaction_handler(
        const NATIVE_INT_TYPE portNum,
        U8 slaveAddress,
        Fw::Buffer &writeBuffer,
        Fw::Buffer &readBuffer
    )
  {
    // Slave address above 127 is a mistake, should only be using bottom 7 bits
    FW_ASSERT(slaveAddress < 128, slaveAddress, 128);

    this->m_err_flag = false;
    this->m_return = Drv::I2cStatus::I2C_OK;

    // Send start condition
    start();
    if (m_err_flag) { stop(); return m_return; }

    if (writeBuffer.getsize() != 0)
    {
      // Send data
      transmit(slaveAddress, (U8*)writeBuffer.getdata(), writeBuffer.getsize());
      if (m_err_flag) { stop(); return m_return; }

      if (readBuffer.getsize() != 0)
      {
        // Repeated start
        start();
        if (m_err_flag) { stop(); return m_return; }

        // Receive data
        receive(slaveAddress, (U8*)readBuffer.getdata(), readBuffer.getsize());
        if (m_err_flag) { stop(); return m_return; }
      }
    }
    else if(readBuffer.getsize() != 0)
    {
      // Receive data
      receive(slaveAddress, (U8*)readBuffer.getdata(), readBuffer.getsize());
      if (m_err_flag) { stop(); return m_return; }
    }

    // Send stop condition and release bus
    stop();

    return m_return;
  }

} // end namespace Drv
