# This is a template for the mod.mk file that goes in each module
# and each module's subdirectories.
# With a fresh checkout, "make gen_make" should be invoked. It should also be
# run if any of the variables are updated. Any unused variables can
# be deleted from the file.

# There are some standard files that are included for reference


SRC = ATmegaI2cDriverComponentAi.xml \
      ATmegaI2cDriverComponentImpl.cpp

SRC_LINUX = ATmegaI2cDriverComponentLinuxImpl.cpp

SRC_ARDUINO = ATmegaI2cDriverComponentAVRImpl.cpp

SRC_RASPIAN = ATmegaI2cDriverComponentLinuxImpl.cpp

HDR = ATmegaI2cDriverComponentImpl.hpp

SUBDIRS =
