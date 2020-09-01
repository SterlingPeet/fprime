# This is a template for the mod.mk file that goes in each module
# and each module's subdirectories.
# With a fresh checkout, "make gen_make" should be invoked. It should also be
# run if any of the variables are updated. Any unused variables can
# be deleted from the file.

# There are some standard files that are included for reference


SRC = EePrmDbAi.xml \
      EePrmDbComponentImpl.cpp

SRC_LINUX = EePrmDbComponentLinuxImpl.cpp

SRC_ARDUINO = EePrmDbComponentArduinoImpl.cpp

SRC_AVR = EePrmDbComponentAVRImpl.cpp

HDR = EePrmDbComponentImpl.hpp

SUBDIRS =
