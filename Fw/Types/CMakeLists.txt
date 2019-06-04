####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Assert.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicTypes.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/EightyCharString.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/InternalInterfaceString.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/MallocAllocator.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/MemAllocator.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/PolyType.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/SerialBuffer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Serializable.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/StringType.cpp"
)
set(MOD_DEPS
  Fw/Cfg
)
register_fprime_module()
if(${CMAKE_SYSTEM_NAME} STREQUAL "ArduinoMega")
    add_arduino_dependency("Fw_Types")
endif()

### UTs ###
set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TypesTest.cpp"
)
set(UT_MOD_DEPS
  "${FPRIME_CORE_DIR}/Os"
)
register_fprime_ut()

# Non-test directory
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/GTest")
