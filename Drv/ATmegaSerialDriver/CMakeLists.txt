####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
####


set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/ATmegaSerialDriverComponentAi.xml"
)

# Check the build is AVR/Arduino
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino" OR ${CMAKE_SYSTEM_NAME} STREQUAL "AVR")
    list(APPEND SOURCE_FILES  "${CMAKE_CURRENT_LIST_DIR}/ATmegaSerialDriverComponentImpl.cpp")
endif()

register_fprime_module()
