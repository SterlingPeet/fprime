// ======================================================================
// \title  ATmegaI2cDriverComponentImpl.hpp
// \author vagrant
// \brief  hpp file for ATmegaI2cDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ATmegaI2cDriver_HPP
#define ATmegaI2cDriver_HPP

#include "Drv/ATmegaI2cDriver/ATmegaI2cDriverComponentAc.hpp"

namespace Drv {

  class ATmegaI2cDriverComponentImpl :
    public ATmegaI2cDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ATmegaI2cDriver
      //!
      ATmegaI2cDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object ATmegaI2cDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! I2C Parameters.
      typedef enum SCL_RATE {
        SCL_100KHZ,
        SCL_400KHZ,
        SCL_1MHZ,
      } I2cClockRate;

      //! Open device with specified clock rate.
      void config(U8 slaveAddress, I2cClockRate scl_rate);

      //! Destroy object ATmegaI2cDriver
      //!
      ~ATmegaI2cDriverComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for i2cRead
      //!
      void i2cTransaction_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 slaveAddress, /*!< I2C slave address of the device*/
          Fw::Buffer &writeBuffer, /*!< Buffer containing write data*/
          Fw::Buffer &readBuffer /*!< Buffer containing data*/
      );

      //! Transmit an I2C start condition
      void start(void);

      //! Transmit an I2C stop condition
      void stop(void);

      //! Transmit data
      void transmit(U8 address, U8* data, U32 len);

      //! Receive data
      void receive(U8 address, U8* data, U32 len);

      //! Write a byte
      void write(U8 data);

      //! Read and request an Ack
      U8 readAck(void);

      //! Read and request NAck
      U8 readNack(void);

      U8 m_address; /*!< The I2C slave address*/
      NATIVE_INT_TYPE m_freq; /*!< The I2C device speed*/

    };

} // end namespace Drv

#endif
