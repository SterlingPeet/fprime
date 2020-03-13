####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####


set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/ATmegaI2cDriverComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/ATmegaI2cDriverComponentImpl.cpp"
)

register_fprime_module()
# Add ArduinoMega dependency
if(${CMAKE_SYSTEM_NAME} STREQUAL "ArduinoMega")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()
