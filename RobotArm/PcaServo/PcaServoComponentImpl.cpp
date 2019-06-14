// ======================================================================
// \title  PcaServoComponentImpl.cpp
// \author vagrant
// \brief  cpp file for PcaServo component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <RobotArm/PcaServo/PcaServoComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace RobotArm {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  PcaServoComponentImpl ::
#if FW_OBJECT_NAMES == 1
    PcaServoComponentImpl(
        const char *const compName
    ) :
      PcaServoComponentBase(compName)
#else
    PcaServoComponentImpl(void)
#endif
  {

  }

  void PcaServoComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    PcaServoComponentBase::init(instance);
  }

  PcaServoComponentImpl ::
    ~PcaServoComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void PcaServoComponentImpl ::
    position_handler(
        const NATIVE_INT_TYPE portNum,
        F32 angle
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void PcaServoComponentImpl ::
    PS_Set_Angle_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        F32 angle
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void PcaServoComponentImpl ::
    PS_Set_Raw_PulseWidth_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        F32 time
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void PcaServoComponentImpl ::
    PS_DIS_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void PcaServoComponentImpl ::
    PS_EN_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

} // end namespace RobotArm
