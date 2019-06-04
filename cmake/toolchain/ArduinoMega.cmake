# Set system name
set(CMAKE_SYSTEM_NAME "ArduinoMega")

# # Location of avr toolchain (ubuntu packaged version)
# set(AVR_TOOLCHAIN "/usr")

# # specify the cross compiler
# set(CMAKE_C_COMPILER "${AVR_TOOLCHAIN}/bin/avr-gcc")
# set(CMAKE_CXX_COMPILER "${AVR_TOOLCHAIN}/bin/avr-g++")

# # where is the target environment
# set(CMAKE_FIND_ROOT_PATH  "${AVR_TOOLCHAIN}/lib/avr")


set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY" CACHE STRING "Try Static Lib Type" FORCE)

# Check if ARDUINO_SDK_PATH is set, otherwise set it to /opt/arduino-1.8.9/
SET(ARDUINO_SDK_PATH "/opt/arduino-1.8.9" CACHE PATH "Path to Arduino SDK")
SET(ARDUINO_VERSION "ATmega2560" CACHE STRING "Version of ARDUINO to use")
SET(ARDUINO_CORE_DIR "arduino")
SET(ARDUINO_VARIANT_DIR "mega")
include("${CMAKE_CURRENT_LIST_DIR}/ArduinoSupport/${ARDUINO_VERSION}.cmake")
set(ARDUINO_SRC_DIR "${ARDUINO_SDK_PATH}/hardware/arduino/avr/cores/${ARDUINO_CORE_DIR}" CACHE PATH "arduino SRC")
set(ARDUINO_VARIANT_SRC_DIR "${ARDUINO_SDK_PATH}/hardware/arduino/avr/variants/${ARDUINO_VARIANT_DIR}")

message(STATUS "Arduino SDK path:  ${ARDUINO_SDK_PATH}")
message(STATUS "Teensy Version:    ${ARDUINO_VERSION}; ${ARDUINO_CORE_DIR}")
message(STATUS "Teensy Source Dir: ${ARDUINO_SRC_DIR}")

# Setup the cross compiling tools path
set(ARDUINO_TOOLS_PATH "${ARDUINO_SDK_PATH}/hardware/tools/${CMAKE_SYSTEM_PROCESSOR}/bin")
message(STATUS "Teensy Tools Dir:  ${ARDUINO_TOOLS_PATH}")

# Grab a suffix for tools
if(WIN32)
    set(TOOL_SUFFIX .exe)
else()
    set(TOOL_SUFFIX )
endif()
# Set the tools path
set(CMAKE_C_COMPILER   "${ARDUINO_TOOLS_PATH}/avr-gcc${TOOL_SUFFIX}"         CACHE PATH "gcc"       FORCE)
set(CMAKE_CXX_COMPILER "${ARDUINO_TOOLS_PATH}/avr-g++${TOOL_SUFFIX}"         CACHE PATH "g++"       FORCE)
set(CMAKE_ASM_COMPILER "${ARDUINO_TOOLS_PATH}/avr-g++${TOOL_SUFFIX}"         CACHE PATH "assembler" FORCE)
set(CMAKE_AR           "${ARDUINO_TOOLS_PATH}/avr-gcc-ar${TOOL_SUFFIX}"      CACHE PATH "archive"   FORCE)
set(CMAKE_LINKER       "${ARDUINO_TOOLS_PATH}/avr-ld${TOOL_SUFFIX}"          CACHE PATH "linker"    FORCE)
set(CMAKE_NM           "${ARDUINO_TOOLS_PATH}/avr-nm${TOOL_SUFFIX}"          CACHE PATH "nm"        FORCE)
set(CMAKE_OBJCOPY      "${ARDUINO_TOOLS_PATH}/avr-objcopy${TOOL_SUFFIX}"     CACHE PATH "objcopy"   FORCE)
set(CMAKE_OBJDUMP      "${ARDUINO_TOOLS_PATH}/avr-objdump${TOOL_SUFFIX}"     CACHE PATH "objdump"   FORCE)
set(CMAKE_STRIP        "${ARDUINO_TOOLS_PATH}/avr-strip${TOOL_SUFFIX}"       CACHE PATH "strip"     FORCE)
set(CMAKE_SIZE         "${ARDUINO_TOOLS_PATH}/avr-size${TOOL_SUFFIX}"        CACHE PATH "size"      FORCE)
set(CMAKE_RANLIB       "${ARDUINO_TOOLS_PATH}/avr-gcc-ranlib${TOOL_SUFFIX}"  CACHE PATH "ranlib"    FORCE)

# Teensy common defines
set(ARDUINO_DEF "-DF_CPU=${ARDUINO_FREQ}") # " -DUSB_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE -D__${ARDUINO_CPU_ARCH}__")
set(ARDUINO_DEF "${ARDUINO_DEF} -DARDUINO=${ARDUINO_ARDUINO_NUM}")
# Teensy flags for each language
set(ARDUINO_COM "-Wall -g -Os -MMD -ffunction-sections -fdata-sections")
set(ARDUINO_CPU "-mmcu=${ARDUINO_CPU_ARCH} ${ARDUINO_CPU_FLAGS}")
set(ARDUINO_C   "-std=c99 -pedantic -Werror-implicit-function-declaration -Wstrict-prototypes")
set(ARDUINO_CPP "-std=gnu++11 -fno-exceptions -fpermissive -fno-rtti -felide-constructors -Wno-error=narrowing")
set(ARDUINO_ASM "-x assembler-with-cpp")
# set(ARDUINO_LD  "-T${ARDUINO_SRC_DIR}/${MCU_LD} -Wl,--gc-sections,--defsym=__rtc_localtime=0") #TODO: fix this time

# Set the tool and language flags
set(CMAKE_C_FLAGS   "${ARDUINO_CPU} ${ARDUINO_COM} ${ARDUINO_DEF} ${ARDUINO_C}"   CACHE STRING "C_FLAGS")
set(CMAKE_CXX_FLAGS "${ARDUINO_CPU} ${ARDUINO_COM} ${ARDUINO_DEF} ${ARDUINO_CPP}" CACHE STRING "CXX_FLAGS")
set(CMAKE_ASM_FLAGS "${ARDUINO_CPU} ${ARDUINO_COM} ${ARDUINO_DEF} ${ARDUINO_ASM}" CACHE STRING "ASM_FLAGS")
set(CMAKE_EXE_LINKER_FLAGS "${ARDUINO_CPU} ${ARDUINO_LD}"                         CACHE STRING "LD_FLAGS")

# Calls into the compiler
set(CMAKE_CXX_COMPILE_OBJECT "${CMAKE_CXX_COMPILER} -c <SOURCE> -o <OBJECT> <FLAGS> <INCLUDES>" CACHE STRING "C++ to o")
set(CMAKE_ASM_COMPILE_OBJECT "${CMAKE_ASM_COMPILER} -c <SOURCE> -o <OBJECT> <FLAGS> <INCLUDES>" CACHE STRING "ASM to o")
set(CMAKE_C_COMPILE_OBJECT   "${CMAKE_C_COMPILER}   -c <SOURCE> -o <OBJECT> <FLAGS> <INCLUDES>" CACHE STRING "C to o")

# Glob up all the files for the Arduino lib build
file(GLOB ARDUINO_SRC "${ARDUINO_SRC_DIR}/*.cpp" "${ARDUINO_SRC_DIR}/*.h" "${ARDUINO_SRC_DIR}/*.c" "${ARDUINO_SRC_DIR}/*.S" "${ARDUINO_SDK_PATH}/hardware/teensy/avr/libraries/TimerOne/*.cpp" "${ARDUINO_SDK_PATH}/hardware/teensy/avr/libraries/TimerOne/*.h")
if (NOT ARDUINO_SRC STREQUAL "")
    set(ARDUINO_ARDUINO_SRC ${ARDUINO_SRC} CACHE STRING "Mega's Arduino Sources")
endif()

####
# add_arduino_dependency:
#
# Adds a dependency on the built version of the Arduino core for the teensy. It also registers a custom command to build
# the hex version of the output file for upload to the teensy itself. This will allow the user to burn to the Teensy
# using the Teensy bootloader utility.
# @param target: target project used to identify the output executable
####
function(add_arduino_dependency target)
    # Build the Arduino core library for Teensy
    if (NOT TARGET "arduinocore")
        add_library("arduinocore" ${ARDUINO_SRC} ${ARDUINO_SHIM_SOURCES})
        target_link_libraries("arduinocore" "m" ${ARDUINO_LIBS})
        target_include_directories("arduinocore" PUBLIC ${ARDUINO_SRC_DIR})
        target_include_directories("arduinocore" PUBLIC ${ARDUINO_VARIANT_SRC_DIR})
        target_include_directories("arduinocore" PUBLIC "${ARDUINO_SDK_PATH}/hardware/teensy/avr/libraries/TimerOne/")
    endif()


    # Add a dependency on the teensycore (Arduino framework build) to the target
    add_dependencies(${target} "arduinocore")
    target_link_libraries(${target} "arduinocore" "m" )
    target_include_directories(${target} PUBLIC ${ARDUINO_SRC_DIR})
    target_include_directories("arduinocore" PUBLIC ${ARDUINO_VARIANT_SRC_DIR})
    target_include_directories("arduinocore" PUBLIC "${ARDUINO_SDK_PATH}/hardware/teensy/avr/libraries/TimerOne/")
    # Check if executable
    get_target_property(target_type ${target} TYPE)
    if (target_type STREQUAL "EXECUTABLE")
        # Add a command to generate the hex, and adding the custom target to link it in
        add_custom_command(OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.hex"
                           COMMAND "${CMAKE_OBJCOPY}"
                           ARGS "-O" "ihex" "-R" ".eeprom" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.hex"
                           DEPENDS "${target}")
        add_custom_target("${target}_hex" ALL DEPENDS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.hex")
    add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_SIZE} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}")
    add_custom_command(TARGET ${target}_hex POST_BUILD COMMAND ${CMAKE_SIZE} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.hex")
    endif()
endfunction()
