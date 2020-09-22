// ======================================================================
// \title  ATmegaSerialDriverComponentArduinoImpl.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  UART driver for operating the hardware UARTs on an ATmega hardware platform (such as ATmega128).
// ======================================================================


#include <Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentImpl.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Types/BasicTypes.hpp>

#include <Arduino.h>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  bool ATmegaSerialDriverComponentImpl ::
    open(
        UartDevice device,
        UartBaudRate baud,
        UartParity parity
    )
  {
      HardwareSerial* serPort;
      switch(device) {
          case USART0:
            serPort = &Serial;
            break;
          case USART1:
            serPort = &Serial1;
            break;
          default:
            FW_ASSERT(0,device);
            break;
      }

      I32 relayRate = 0;
      switch (baud) {
          case BAUD_9600:
              relayRate = 9600;
              break;
          case BAUD_19200:
              relayRate = 19200;
              break;
          case BAUD_38400:
              relayRate = 38400;
              break;
          case BAUD_57600:
              relayRate = 57600;
              break;
          case BAUD_115K:
              relayRate = 115200;
              break;
          default:
              FW_ASSERT(0,baud);
              break;
      }

      // Start the serial device
      serPort->begin(relayRate);

      return true;
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ATmegaSerialDriverComponentImpl ::
    serialRecv_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &serBuffer,
        SerialReadStatus &status
    )
  {
    HardwareSerial* serPort;
    if(portNum == 0)
    {
      serPort = &Serial;
    }
    else
    {
      serPort = &Serial1;
    }
    NATIVE_INT_TYPE i = 0;
    U8* readBuf = reinterpret_cast<U8*>(serBuffer.getdata());
    FW_ASSERT(serBuffer.getsize()>0, serBuffer.getsize());
    while(serPort->available() > 0 && i < serBuffer.getsize())
    {
      readBuf[i] = serPort->read();
      i++;
    }
    serBuffer.setsize(i);
    this->m_UartBytesRecv[portNum] += i;
  }

  void ATmegaSerialDriverComponentImpl ::
    serialSend_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &serBuffer
    )
  {
    HardwareSerial* serPort;
    if(portNum == 0)
    {
      serPort = &Serial;
    }
    else
    {
      serPort = &Serial1;
    }
    FW_ASSERT(serBuffer.getsize()>0, serBuffer.getsize());
    serPort->write((U8*)serBuffer.getdata(), serBuffer.getsize());
    this->m_UartBytesSent[portNum] += serBuffer.getsize();
  }

  void ATmegaSerialDriverComponentImpl ::
    serialRecvFwBuf_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    HardwareSerial* serPort;
    if(portNum == 0)
    {
      serPort = &Serial;
    }
    else
    {
      serPort = &Serial1;
    }
    NATIVE_INT_TYPE i = 0;
    U8* readBuf = reinterpret_cast<U8*>(fwBuffer.getdata());
    FW_ASSERT(fwBuffer.getsize()>0, fwBuffer.getsize());
    while(serPort->available() > 0 && i < fwBuffer.getsize())
    {
      readBuf[i] = serPort->read();
      i++;
    }
    fwBuffer.setsize(i);
    this->m_UartBytesRecv[portNum] += i;
  }

  void ATmegaSerialDriverComponentImpl ::
    serialSendFwBuf_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    HardwareSerial* serPort;
    if(portNum == 0)
    {
      serPort = &Serial;
    }
    else
    {
      serPort = &Serial1;
    }
    FW_ASSERT(fwBuffer.getsize()>0, fwBuffer.getsize());
    serPort->write((U8*)fwBuffer.getdata(), fwBuffer.getsize());
    this->m_UartBytesSent[portNum] += fwBuffer.getsize();
  }

} // end namespace Drv
