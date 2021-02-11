####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/I2cGenericTopologyAppAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/Main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Topology.cpp"
)
# Note: supply non-explicit dependencies here
set(MOD_DEPS
    Fw/Logger
    Svc/LinuxTime
    # Os
    Os/Baremetal/TaskRunner
    ATmega/vendor/libraries/MemoryFree
)

register_fprime_executable()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    add_arduino_dependency("${PROJECT_NAME}")
endif()
