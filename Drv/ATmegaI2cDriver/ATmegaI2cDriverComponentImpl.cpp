// ======================================================================
// \title  ATmegaI2cDriverComponentImpl.cpp
// \author vagrant
// \brief  cpp file for ATmegaI2cDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include "Drv/ATmegaI2cDriver/ATmegaI2cDriverComponentImpl.hpp"
#include "Fw/Types/BasicTypes.hpp"

#include <avr/io.h>
#include <util/twi.h>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ATmegaI2cDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ATmegaI2cDriverComponentImpl(
        const char *const compName
    ) :
      ATmegaI2cDriverComponentBase(compName)
#else
    ATmegaI2cDriverComponentImpl(void)
#endif
  ,m_address(0)
  ,m_freq(0)
  {

  }

  void ATmegaI2cDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ATmegaI2cDriverComponentBase::init(instance);
  }

  void ATmegaI2cDriverComponentImpl ::
    config(
        U8 slaveAddress,
        I2cClockRate scl_rate
    )
  {
    m_address = slaveAddress;

    switch (scl_rate) {
      case SCL_100KHZ:
        m_freq = 100000L;
        break;
      case SCL_400KHZ:
        m_freq = 400000L;
        break;
      case SCL_1MHZ:
        m_freq = 1000000L;
        break;
    }

    /*
     * From the ATmega128 datasheet:
     *  TWBR = ( (CPU Clock freq)/(SCL freq) - 16 ) / ( 2 * 4^(Prescalar value) )
     *
     * Disable prescalar value in TWSR and set TWBR according to CPU freq and SCL freq.
     */
    TWSR &= ~(_BV(TWPS1) | _BV(TWPS0));
    TWBR = ( (F_CPU/m_freq) - 16 ) / (2 * 4);
  }

  ATmegaI2cDriverComponentImpl ::
    ~ATmegaI2cDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ATmegaI2cDriverComponentImpl ::
    i2cTransaction_handler(
        const NATIVE_INT_TYPE portNum,
        U8 slaveAddress,
        Fw::Buffer &writeBuffer,
        Fw::Buffer &readBuffer
    )
  {
    // Send start condition
    start();

    // Check if start condition was sucessfully transmitted
    if (TW_STATUS != TW_START) // TODO: SOMETHING
    {    }

    if (writeBuffer.getsize() != 0)
    {
      // Send data
      transmit(slaveAddress, writeBuffer.getdata(), writeBuffer.getsize());

      if (readBuffer.getsize() != 0)
      {
        // Repeated start
        start();

        // Receive data
        receive(slaveAddress, readBuffer.getdata(), readBuffer.getsize());
      }
    }
    else if(readBuffer.getsize() != 0)
    {
      // Receive data
      receive(slaveAddress, readBuffer.getdata(), readBuffer.getsize());
    }

    // Send stop condition and release bus
    stop();
  }

  //! Transmit an I2C start condition
  void ATmegaI2cDriverComponentImpl ::
    start(void)
  {

    // Serial.println("\n start");
    // Send start condition
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    // Serial.println("sent start");
    // printTWCR();
    // delay(200);
    // printTWCR();
    // Wait for TWINT to be set to confirm transmission
    while(!(TWCR & _BV(TWINT)))
    {
      // Serial.print("TWCR: 0x");
      // Serial.println(TWCR);
    }
    // Serial.println("started.");
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
    if ((TWSR & 0xF8) != TW_MT_SLA_ACK) // TODO: SOMETHING
    {

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
    TWCR = _BV(TWINT) | _BV(TWEN);

    // Wait for end of transmission
    while(!(TWCR & _BV(TWINT)));
  }

  U8 ATmegaI2cDriverComponentImpl ::
    readAck(void)
  {
    // Start receive with an acknowledge
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);

    // Wait for end of transmission
    while(!(TWCR & _BV(TWINT)));

    // Return received data
    return TWDR;
  }

  U8 ATmegaI2cDriverComponentImpl ::
    readNack(void)
  {
    // Start receive without an acknowledge
    TWCR = _BV(TWINT) | _BV(TWEN);

    // Wait for end of transmission
    while(!(TWCR & _BV(TWINT)));

    // Return received data
    return TWDR;
  }


} // end namespace Drv
