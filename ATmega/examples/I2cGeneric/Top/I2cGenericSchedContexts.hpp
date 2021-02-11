// ======================================================================
// \title  I2cGenericSchedContexts.hpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Generic I2C deployment for testing I2C commands with arbitrary commanded data.
// ======================================================================


#ifndef I2CGENERIC_TOP_I2CGENERICSCHEDCONTEXTS_HPP_
#define I2CGENERIC_TOP_I2CGENERICSCHEDCONTEXTS_HPP_

namespace I2cGeneric {
    // A list of contexts for the rate groups
    enum {
        // CONTEXT_I2CGENERIC_1Hz = 10, // 1 Hz cycle
        CONTEXT_I2CGENERIC_10Hz = 11 // 10 Hz cycle
    };
}  // end I2cGeneric

#endif /* I2CGENERIC_TOP_I2CGENERICSCHEDCONTEXTS_HPP_ */
