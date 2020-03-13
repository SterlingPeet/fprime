// ======================================================================
// \title  ATmegaSpiDriverComponentImpl.hpp
// \author vagrant
// \brief  hpp file for ATmegaSpiDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ATmegaSpiDriver_HPP
#define ATmegaSpiDriver_HPP

#include "Drv/ATmegaSpiDriver/ATmegaSpiDriverComponentAc.hpp"

#include <avr/io.h>

namespace Drv {

  class ATmegaSpiDriverComponentImpl :
    public ATmegaSpiDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ATmegaSpiDriver
      //!
      ATmegaSpiDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      typedef enum SPI_MODE {
        SPI_MODE_0 = 0,
        SPI_MODE_1,
        SPI_MODE_2,
        SPI_MODE_3
      } SpiMode;

      //! Initialize object ATmegaSpiDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Configure SPI driver
      //!
      void open(
          volatile uint8_t &ss_data_dir_register,
          volatile uint8_t &ss_port_register,
          int ss_pin_number,
          SpiMode spi_mode = SPI_MODE_0
      );

      //! Destroy object ATmegaSpiDriver
      //!
      ~ATmegaSpiDriverComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for SpiReadWrite
      //!
      void SpiReadWrite_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &writeBuffer,
          Fw::Buffer &readBuffer
      );

      //! Data Direction Register for SS pin (needs to match m_ss_port)
      volatile uint8_t *m_ss_ddir;

      //! Port Register for SS pin (needs to match m_ss_ddir)
      volatile uint8_t *m_ss_port;

      //! SS Pin Number within Port
      uint8_t m_ss_pin;

    };

} // end namespace Drv

#endif
