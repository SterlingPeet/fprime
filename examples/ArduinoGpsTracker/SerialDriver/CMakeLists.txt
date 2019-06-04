####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/SerialDriverComponentAi.xml"
  "${CMAKE_CURRENT_LIST_DIR}/SerialDriver.cpp"
)
# Teensyduino additions
if(${CMAKE_SYSTEM_NAME} STREQUAL "Teensyduino")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/SerialDriverArduino.cpp")
# Teensyduino additions
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "ArduinoMega")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/SerialDriverArduino.cpp")
# Check the Linux build
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/SerialDriverLinux.cpp")
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
