####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverComponentAi.xml"
  "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriver.cpp"
)
# Teensyduino additions
if(${CMAKE_SYSTEM_NAME} STREQUAL "Teensyduino")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverTeensy.cpp")
# Teensyduino additions
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "ArduinoMega")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverArduino.cpp")
# Check the Linux build
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverLinux.cpp")
endif()
register_fprime_module()
# Add Teensyduino dependency
if(${CMAKE_SYSTEM_NAME} STREQUAL "Teensyduino")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()

# Add Arduino dependency
if(${CMAKE_SYSTEM_NAME} STREQUAL "ArduinoMega")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()
