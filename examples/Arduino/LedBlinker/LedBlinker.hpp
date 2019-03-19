// ====================================================================== 
// \title  LedBlinkerImpl.hpp
// \author lestarch
// \brief  hpp file for LedBlinker component implementation class
//
// ====================================================================== 

#ifndef LedBlinker_HPP
#define LedBlinker_HPP

#include "examples/Arduino/LedBlinker/LedBlinkerComponentAc.hpp"

namespace Arduino {

  class LedBlinkerComponentImpl :
    public LedBlinkerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object LedBlinker
      //!
      LedBlinkerComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object LedBlinker
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object LedBlinker
      //!
      ~LedBlinkerComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );
      U32 m_counter;
      U32 m_cap;
      bool m_state;
    };

} // end namespace Arduino

#endif