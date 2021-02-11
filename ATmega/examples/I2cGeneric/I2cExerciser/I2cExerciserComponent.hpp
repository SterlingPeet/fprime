// ======================================================================
// \title  I2cExerciserComponent.hpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example component to support I2cGeneric deployment.
// ======================================================================

#ifndef I2cExerciserComponent_HPP
#define I2cExerciserComponent_HPP

#include "ATmega/examples/I2cGeneric/I2cExerciser/I2cExerciserComponentAc.hpp"

#ifndef I2C_EXERCISER_TX_BUFF_LEN
  #define I2C_EXERCISER_TX_BUFF_LEN 32
#endif
#ifndef I2C_EXERCISER_RX_BUFF_LEN
  #define I2C_EXERCISER_RX_BUFF_LEN 32
#endif

namespace examples {

  class I2cExerciserComponent :
    public I2cExerciserComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object I2cExerciserComponent
      //!
      I2cExerciserComponent(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object I2cExerciserComponent
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object I2cExerciserComponent
      //!
      ~I2cExerciserComponent(void);

    PRIVATE:
      bool m_state;
      U32 m_blinks;
      U32 m_blinkDecimateCntrl;

      BYTE m_writeBufferData[I2C_EXERCISER_TX_BUFF_LEN];
      Fw::Buffer m_writeBuffer;

      BYTE m_readBufferData[I2C_EXERCISER_RX_BUFF_LEN];
      Fw::Buffer m_readBuffer;
      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for i2cTransaction command handler
      //! Instigate a custom I2C transaction, and telemeter the response.
      void i2cTransaction_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 address, /*!< Address of i2c slave*/
          U8 txLength, /*!< number of bytes to send to i2c slave*/
          U8 rxLength /*!< maximum number of bytes to recieve from i2c slave*/
      );

      //! Implementation for loadTxData command handler
      //! prep I2C tx buffer for next trasaction, one byte at a time
      void loadTxData_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 index, /*!< Zero indexed position of the data byte*/
          U8 data /*!< data byte to load into buffer*/
      );

      //! Implementation for downlinkI2CBuffers command handler
      //! send the buffer contents to the ground
      void downlinkI2CBuffers_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for downlinkI2CBufferSizes command handler
      //! send the buffer sizes/lengths to the ground
      void downlinkI2CBufferSizes_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for downlinkParams command handler
      //! Command to telemeter the current parameter values in use.
      void downlinkParams_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Blink a given pin
      void blink();
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );
      //! parameter update notification
      //!
      void parameterUpdated(FwPrmIdType id);

    };

} // end namespace examples

#endif // end I2cExerciserComponent_HPP
