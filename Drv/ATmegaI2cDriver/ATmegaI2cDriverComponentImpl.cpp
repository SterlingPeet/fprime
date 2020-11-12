// ======================================================================
// \title  ATmegaI2cDriverComponentImpl.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  I2C driver for operating the I2C bus on an ATmega hardware platform (such as ATmega128).
// ======================================================================


#include "Drv/ATmegaI2cDriver/ATmegaI2cDriverComponentImpl.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"

// TODO: Separate the code cleanly enough that AVR specific things are
//       all in the AVR Impl cpp file.
#ifdef __AVR__
  #include <util/atomic.h>
#endif

#ifdef DEBUG_I2C_AVR || DEBUG_I2C_AVR_Q
  #ifdef ARDUINO
    #include <Arduino.h>
    #ifndef DEBUG_Serial
      #define DEBUG_Serial Serial
    #endif
  #endif
#endif

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
    ,m_state(I2C_DRV_STATE::TRANS_IDLE)
    ,m_q_len(0)
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
    // Check that at least one of the buffers is non-zero length
    FW_ASSERT(writeBuffer.getsize() > 0 || readBuffer.getsize() > 0);

    bool start_flag = false;
    Drv::I2cStatus ret = I2cStatus::I2C_OK;

#ifdef DEBUG_I2C_AVR
    DEBUG_Serial.print(F("I2c txn to "));
    DEBUG_Serial.println(slaveAddress);
    DEBUG_Serial.print(F("I2c state "));
    if(m_state == I2C_DRV_STATE::TRANS_IDLE)
    {
      DEBUG_Serial.println(F("IDLE"));
    }
    else
    {
      DEBUG_Serial.println(F("IN_PROG"));
    }
#endif

#ifdef __AVR__
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
#endif
      if(m_state == I2C_DRV_STATE::TRANS_IN_PROGRESS)
      {
        if(m_q_len < I2C_QUEUE_LENGTH)
        {
#ifdef DEBUG_I2C_AVR_Q
          DEBUG_Serial.print(F("I2c Q len "));
          DEBUG_Serial.println(m_q_len);
#endif
          m_q_slaveAddress[m_q_len] = slaveAddress;
          m_q_writeBuffer[m_q_len] = writeBuffer;
          m_q_readBuffer[m_q_len] = readBuffer;
          m_q_len += 1;
        }
        else
        {
          // This happens because the internal queue is full
          ret = I2cStatus::I2C_OTHER_ERR;
#ifdef DEBUG_I2C_AVR_Q
          DEBUG_Serial.println(F("I2c Q full"));
#endif
        }
      }
#ifdef __AVR__
    }
#endif

#ifdef __AVR__
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
#endif
      if(m_state == I2C_DRV_STATE::TRANS_IDLE)
      {
#ifdef DEBUG_I2C_AVR
        DEBUG_Serial.println(F("I2c State IN_PROG"));
#endif
        m_state = I2C_DRV_STATE::TRANS_IN_PROGRESS;
        start_flag = true;
      }
#ifdef __AVR__
    }
#endif

    if(start_flag)
    {
#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.println(F("I2c Start TXN"));
#endif
      ret = this->execute_txn(slaveAddress,
                              writeBuffer,
                              readBuffer);
    }

#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.print(F("I2c Q len "));
      DEBUG_Serial.println(m_q_len);
#endif

    // After running the base transaction, unspool the queue
    while(m_state == I2C_DRV_STATE::TRANS_IN_PROGRESS)
    {
      start_flag = false;
#ifdef __AVR__
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
      {
#endif
        if(m_q_len > 0)
        {
          // FIFO: Set up the next txn from index 0
          m_q_len -= 1;
          slaveAddress = m_q_slaveAddress[0];
          writeBuffer = m_q_writeBuffer[0];
          readBuffer = m_q_readBuffer[0];
          // Move each pointer one index closer to index 0
          for(U8 i=1; i<=m_q_len; i++)
          {
            m_q_slaveAddress[i-1] = m_q_slaveAddress[i];
            m_q_writeBuffer[i-1] = m_q_writeBuffer[i];
            m_q_readBuffer[i-1] = m_q_readBuffer[i];
          }
          start_flag = true;
        }
#ifdef __AVR__
      }
#endif
      if(start_flag)
      {
#ifdef DEBUG_I2C_AVR_Q
        DEBUG_Serial.println(F("I2c Start Q TXN"));
#endif
        this->execute_txn(slaveAddress,
                          writeBuffer,
                          readBuffer);
      }
#ifdef __AVR__
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
      {
#endif
        if(m_q_len == 0)
        {
          m_state = I2C_DRV_STATE::TRANS_IDLE;
#ifdef DEBUG_I2C_AVR
          DEBUG_Serial.println(F("I2c State IDLE"));
#endif
        }
#ifdef __AVR__
      }
#endif
    }

    return ret;  // Oh man, tracking this return value is a pain
  }

  Drv::I2cStatus ATmegaI2cDriverComponentImpl ::
    execute_txn(
        U8 slaveAddress, /*!< I2C slave address of the device*/
        Fw::Buffer &writeBuffer, /*!< Buffer containing write data*/
        Fw::Buffer &readBuffer /*!< Buffer containing data*/
    )
  {
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
