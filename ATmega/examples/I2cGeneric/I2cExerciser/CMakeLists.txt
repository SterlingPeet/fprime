####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/I2cExerciserComponentAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/I2cExerciserComponent.cpp"
)


# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

# set(MOD_DEPS
#     Fw/Logger
# )

register_fprime_module()


