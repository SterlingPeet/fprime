// ======================================================================
// \title  ATmegaI2cDriverComponentImplAVR.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  I2C driver for operating the I2C bus on an ATmega hardware platform (such as ATmega128).
// ======================================================================


#include "Drv/ATmegaI2cDriver/ATmegaI2cDriverComponentImpl.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"

#include <avr/io.h>
#include <util/twi.h>

#include "Arduino.h"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  void ATmegaI2cDriverComponentImpl ::
    config(
        I2cClockRate scl_rate
    )
  {
    switch (scl_rate) {
      case SCL_100KHZ:
        m_freq = 100000L;
        break;
      case SCL_400KHZ:
        m_freq = 400000L;
        break;
      case SCL_1MHZ:
        // m_freq = 1000000L;
        FW_ASSERT(0); // Bus Frequency Not Supported
        break;
    }

    /*
     * From the ATmega128 datasheet:
     *  TWBR = ( (CPU Clock freq)/(SCL freq) - 16 ) / ( 2 * 4^(Prescalar value) )
     *
     * Disable prescalar value in TWSR and set TWBR according to CPU freq and SCL freq.
     */
    TWSR &= ~(_BV(TWPS1) | _BV(TWPS0));
    TWBR = ( (F_CPU/m_freq) - 16 ) / (2 * 1);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  //! Transmit an I2C start condition
  void ATmegaI2cDriverComponentImpl ::
    start(void)
  {
    // Send start condition
    TW_timeout(_BV(TWINT) | _BV(TWSTA) | _BV(TWEN));

    if(this->m_err_flag)
    {
      m_return = Drv::I2cStatus::I2C_START_TIMEOUT_ERR;
    }

    // Check if start condition or repeated start condition was sucessfully transmitted
    if (TW_STATUS != TW_START && TW_STATUS != TW_REP_START) // TODO: this is not cross platform
    {
      Serial.println("Err flag 1");
      m_err_flag = true;
      m_return = Drv::I2cStatus::I2C_START_ERR;
    }
  }

  //! Transmit an I2C stop condition
  void ATmegaI2cDriverComponentImpl ::
    stop(void)
  {
    // Send stop condition
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
  }

  void ATmegaI2cDriverComponentImpl ::
    transmit(U8 address, U8* data, U32 len)
  {
    // Write the slave address
    write((address << 1) | TW_WRITE);

    // Check if we received an ACK
    if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
    {
      m_err_flag = true;
      m_return = Drv:: I2cStatus::I2C_ADDRESS_ERR;
    }

    for (NATIVE_UINT_TYPE i = 0; i < len; i++)
    {
      write(data[i]);
    }
  }

  void ATmegaI2cDriverComponentImpl ::
    receive(U8 address, U8* data, U32 len)
  {
    // Write the slave address and set Read bit
    write((address << 1) | TW_READ);

    // Check if we received an ACK
    if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
    {
      // m_err_flag = true;
      // m_return = Drv:: I2cStatus::I2C_ADDRESS_ERR;
    }

    // Check length to see if reading one byte
    if (len == 1)
    {
      // Read byte and NACK
      data[0] = readNack();
    }
    else
    {
      // Read byte and ACK
      for (NATIVE_UINT_TYPE i = 0; i < len - 1; i++)
      {
        data[i] = readAck();
      }
      data[len - 1] = readNack();
    }
  }

  void ATmegaI2cDriverComponentImpl ::
    write(U8 data)
  {
    // Load into into data register
    TWDR = data;

    // Start transmission of data
    TW_timeout(_BV(TWINT) | _BV(TWEN));

    if(this->m_err_flag)
    {
      this->m_return = Drv::I2cStatus::I2C_START_TIMEOUT_ERR;
    }
  }

  U8 ATmegaI2cDriverComponentImpl ::
    readAck(void)
  {
    // Start receive with an acknowledge
    TW_timeout(_BV(TWINT) | _BV(TWEN) | _BV(TWEA));

    if(this->m_err_flag)
    {
      this->m_return = Drv::I2cStatus::I2C_READ_ERR;
    }

    // Return received data
    return TWDR;
  }

  U8 ATmegaI2cDriverComponentImpl ::
    readNack(void)
  {
    // Start receive without an acknowledge
    TW_timeout(_BV(TWINT) | _BV(TWEN));

    if(this->m_err_flag)
    {
      this->m_return = Drv::I2cStatus::I2C_READ_ERR;
    }

    // Return received data
    return TWDR;
  }

  void ATmegaI2cDriverComponentImpl ::
    TW_timeout(U8 twcr)
  {
    TWCR = twcr;

    if(!(TWCR & _BV(TWINT))) // Don't bother setting up timers to drop straight through
    {
      this->m_timer.start(); // set begin time to now
      this->m_timer.stop();  // zero the timer

      // Wait for TWINT to be set to confirm transmission
      while(!(TWCR & _BV(TWINT)) && (m_timer.getDiffUsec() < m_timeout))
      {
        this->m_timer.stop();
      }
      // If we dropped out of the while loop but the TWINT bit is not
      // set, we timed out!
      if(!(TWCR & _BV(TWINT)))
      {
        this->m_err_flag = true;
      }
    }
  }

} // end namespace Drv
