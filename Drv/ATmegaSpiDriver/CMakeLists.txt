####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
####

set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/ATmegaSpiDriverComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/ATmegaSpiDriverComponentImplCommon.cpp"
)

# Determine the platform specific source files to append:
string(TOLOWER "${CMAKE_SYSTEM_NAME}" CMAKE_SYSTEM_NAME_LOWER)

# Arduino additions
if(${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "arduino")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ATmegaSpiDriverComponentImplAVR.cpp")
# AVR platform additions
elseif(${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "avr")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ATmegaSpiDriverComponentImplAVR.cpp")
# Otherwise, assume Linux-compatible build
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ATmegaSpiDriverComponentImplLinux.cpp")
endif()

register_fprime_module()
