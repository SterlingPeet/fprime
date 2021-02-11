// ======================================================================
// \title  I2cExerciserComponent.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example component to support I2cGeneric deployment.
// ======================================================================


#include <ATmega/examples/I2cGeneric/I2cExerciser/I2cExerciserComponent.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace examples {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  I2cExerciserComponent ::
#if FW_OBJECT_NAMES == 1
    I2cExerciserComponent(
        const char *const compName
    ) :
      I2cExerciserComponentBase(compName),
#else
    I2cExerciserComponent(void) :
#endif
    m_state(false),
    m_blinks(0),
    m_blinkDecimateCntrl(0)
  {
    m_writeBuffer.setdata((U64)m_writeBufferData);
    m_writeBuffer.setsize(I2C_EXERCISER_TX_BUFF_LEN);
    m_readBuffer.setdata((U64)m_readBufferData);
    m_readBuffer.setsize(I2C_EXERCISER_RX_BUFF_LEN);
  }

  void I2cExerciserComponent ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    I2cExerciserComponentBase::init(instance);
  }

  void I2cExerciserComponent ::
    blink()
  {
    this->gpio_out(0, m_state);
  }

  I2cExerciserComponent ::
    ~I2cExerciserComponent(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void I2cExerciserComponent ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    Fw::ParamValid valid;
    m_blinkDecimateCntrl++;

    if(m_blinkDecimateCntrl >= this->paramGet_blinkDecimate(valid))
    {
      blink();
      m_state = !m_state;
      m_blinkDecimateCntrl = 0;

      if(m_state)
      {
        m_blinks++;
        tlmWrite_numBlinks(m_blinks);
      }
    }
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void I2cExerciserComponent ::
    i2cTransaction_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 address,
        U8 txLength,
        U8 rxLength
    )
  {
    bool flag = true;
    if(address > 127)
    {
      this->log_WARNING_HI_i2cAddressOutOfRange(address);
      flag = false;
    }
    if(txLength >= I2C_EXERCISER_TX_BUFF_LEN)
    {
      this->log_WARNING_HI_txLengthTooLarge(txLength,I2C_EXERCISER_TX_BUFF_LEN);
      flag = false;
    }
    if(rxLength >= I2C_EXERCISER_RX_BUFF_LEN)
    {
      this->log_WARNING_HI_rxLengthTooLarge(rxLength,I2C_EXERCISER_RX_BUFF_LEN);
      flag = false;
    }
    if(flag)
    {
      m_writeBuffer.setsize(txLength);
      m_readBuffer.setsize(rxLength);
      this->tlmWrite_i2cTxBuffLen((U8)m_writeBuffer.getsize());
      this->tlmWrite_i2cRxBuffLen((U8)m_readBuffer.getsize());
      this->i2cBus_out(0,address,m_writeBuffer,m_readBuffer);
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
    }
    else
    {
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_VALIDATION_ERROR);
    }
  }

  void I2cExerciserComponent ::
    loadTxData_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 index,
        U8 data
    )
  {
    if(index < I2C_EXERCISER_TX_BUFF_LEN)
    {
      m_writeBufferData[index] = data;
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
    }
    else
    {
      this->log_WARNING_LO_txBufferLoadRequestOutOfRange(data,index,I2C_EXERCISER_TX_BUFF_LEN-1);
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_VALIDATION_ERROR);
    }
  }

  void I2cExerciserComponent ::
    downlinkI2CBuffers_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    FW_ASSERT(m_writeBuffer.getsize() <= I2C_EXERCISER_TX_BUFF_LEN);
    FW_ASSERT(m_readBuffer.getsize() <= I2C_EXERCISER_RX_BUFF_LEN);
    for(U8 i=0; i<((m_readBuffer.getsize()-1)/8+1); i++)
    {
      U8 data[8];
      for(U8 j=0; j<8; j++)
      {
        U8 ind = 8*i + j;
        if(ind < m_readBuffer.getsize())
        {
          data[j] = m_readBufferData[ind];
        }
        else
        {
          data[j] = 0;
        }
      }
      this->log_ACTIVITY_HI_I2cRxData(i*8,
                                      data[0],
                                      data[1],
                                      data[2],
                                      data[3],
                                      data[4],
                                      data[5],
                                      data[6],
                                      data[7]);
    }
    for(U8 i=0; i<((m_writeBuffer.getsize()-1)/8+1); i++)
    {
      U8 data[8];
      for(U8 j=0; j<8; j++)
      {
        U8 ind = 8*i + j;
        if(ind < m_writeBuffer.getsize())
        {
          data[j] = m_writeBufferData[ind];
        }
        else
        {
          data[j] = 0;
        }
      }
      this->log_ACTIVITY_HI_I2cTxData(i*8,
                                      data[0],
                                      data[1],
                                      data[2],
                                      data[3],
                                      data[4],
                                      data[5],
                                      data[6],
                                      data[7]);
    }
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void I2cExerciserComponent ::
    downlinkI2CBufferSizes_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    this->tlmWrite_i2cTxBuffLen((U8)m_writeBuffer.getsize());
    this->tlmWrite_i2cRxBuffLen((U8)m_readBuffer.getsize());
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void I2cExerciserComponent ::
    downlinkParams_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    Fw::ParamValid valid;
    U8 val1 = this->paramGet_blinkDecimate(valid);
    this->tlmWrite_blinkDecimate(val1);
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void I2cExerciserComponent ::
    parameterUpdated(
        FwPrmIdType id
    )
  {
    this->log_ACTIVITY_LO_I2cExerciserParameterUpdated(id);
    Fw::ParamValid valid;
    switch(id) {
      case PARAMID_BLINKDECIMATE: {
        U8 val = this->paramGet_blinkDecimate(valid);
        this->tlmWrite_blinkDecimate(val);
        break;
      }
      default:
        FW_ASSERT(0,id);
        break;
    }
  }

} // end namespace examples
