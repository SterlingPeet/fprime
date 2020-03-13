####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####

set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/ATmegaGpioDriverComponentAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/ATmegaGpioDriverComponentImpl.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ATmegaGpioDriverComponentImplCommon.cpp"
)

register_fprime_module()
