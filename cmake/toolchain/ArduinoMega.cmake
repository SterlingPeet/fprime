# Set system name
set(CMAKE_SYSTEM_NAME "ArduinoMega")

# Location of pi toolchain
set(AVR_TOOLCHAIN "/usr")

# specify the cross compiler
set(CMAKE_C_COMPILER "${AVR_TOOLCHAIN}/bin/avr-gcc")
set(CMAKE_CXX_COMPILER "${AVR_TOOLCHAIN}/bin/avr-g++")

# where is the target environment
set(CMAKE_FIND_ROOT_PATH  "${AVR_TOOLCHAIN}/lib/avr")

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
