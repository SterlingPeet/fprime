// ======================================================================
// \title  PcaServoComponentImpl.hpp
// \author vagrant
// \brief  hpp file for PcaServo component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef PcaServo_HPP
#define PcaServo_HPP

#include "RobotArm/PcaServo/PcaServoComponentAc.hpp"

namespace RobotArm {

  class PcaServoComponentImpl :
    public PcaServoComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object PcaServo
      //!
      PcaServoComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object PcaServo
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object PcaServo
      //!
      ~PcaServoComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for position
      //!
      void position_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 angle 
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for PS_Set_Angle command handler
      //! Command to set angle of servo
      void PS_Set_Angle_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 angle /*!< Commanded servo angle*/
      );

      //! Implementation for PS_Set_Raw_PulseWidth command handler
      //! Command to set pulse width in milliseconds
      void PS_Set_Raw_PulseWidth_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 time /*!< Commanded pulse width time in milliseconds*/
      );

      //! Implementation for PS_DIS command handler
      //! Disable servo board
      void PS_DIS_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for PS_EN command handler
      //! Enable servo board
      void PS_EN_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace RobotArm

#endif
