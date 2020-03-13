// ======================================================================
// \title  ATmegaSerialDriverComponentImpl.hpp
// \author vagrant
// \brief  hpp file for ATmegaSerialDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ATmegaSerialDriver_HPP
#define ATmegaSerialDriver_HPP

#include <Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentAc.hpp>
#include <Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentImplCfg.hpp>
#include <Utils/Types/CircularBuffer.hpp>

namespace Drv {

  class ATmegaSerialDriverComponentImpl :
    public ATmegaSerialDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ATmegaSerialDriver
      //!
      ATmegaSerialDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object ATmegaSerialDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Configure UART parameters
      typedef enum DEVICE {
        USART0,
        USART1
      } UartDevice;

      typedef enum BAUD_RATE {
          BAUD_9600,
          BAUD_19200,
          BAUD_38400,
          BAUD_57600,
          BAUD_115K,
          BAUD_230K,
          BAUD_460K,
          BAUD_921K
      } UartBaudRate;

      typedef enum PARITY  {
          PARITY_NONE,
          PARITY_ODD,
          PARITY_EVEN
      } UartParity;

      // Open device with specified baud and parity.
      bool open(UartDevice device, UartBaudRate baud);

      //! Destroy object ATmegaSerialDriver
      //!
      ~ATmegaSerialDriverComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for serialRecv
      //!
      void serialRecv_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &serBuffer, /*!< Buffer containing data*/
          SerialReadStatus &status /*!< Status of read*/
      );

      //! Handler implementation for serialSend
      //!
      void serialSend_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &serBuffer 
      );

      //! Transmit a byte array
      //!
      void transmit(
          U8* data, /*!< Pointer to data buffer*/
          const NATIVE_UINT_TYPE len  /*!< Length of data to transmit*/
      );

      UartDevice m_device;  //!< USART device

    };

} // end namespace Drv

#endif
