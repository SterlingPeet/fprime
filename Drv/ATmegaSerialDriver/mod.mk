# This is a template for the mod.mk file that goes in each module
# and each module's subdirectories.
# With a fresh checkout, "make gen_make" should be invoked. It should also be
# run if any of the variables are updated. Any unused variables can
# be deleted from the file.

# There are some standard files that are included for reference


SRC = ATmegaSerialDriverComponentAi.xml \
      ATmegaSerialDriverComponentImpl.cpp

SRC_LINUX = ATmegaSerialDriverComponentLinuxImpl.cpp

HDR = ATmegaSerialDriverComponentImpl.hpp

SUBDIRS =
