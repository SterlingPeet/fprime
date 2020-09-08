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

# Arduino additions
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ATmegaSpiDriverComponentImplAVR.cpp")
# Check the Linux build
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ATmegaSpiDriverComponentImplLinux.cpp")
endif()

register_fprime_module()
