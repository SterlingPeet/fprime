####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/FatalHandlerComponentAi.xml"
  "${CMAKE_CURRENT_LIST_DIR}/FatalHandlerComponentCommonImpl.cpp"
)
if(${CMAKE_SYSTEM_NAME} STREQUAL "VxWorks")
  set(SOURCE_FILES "${SOURCE_FILES}"
    "${CMAKE_CURRENT_LIST_DIR}/FatalHandlerComponentLinuxImpl.cpp"
  )
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "AVR")
  set(SOURCE_FILES "${SOURCE_FILES}"
    "${CMAKE_CURRENT_LIST_DIR}/FatalHandlerComponentBaremetalImpl.cpp"
  )
else()
  set(SOURCE_FILES "${SOURCE_FILES}"
    "${CMAKE_CURRENT_LIST_DIR}/FatalHandlerComponentLinuxImpl.cpp"
  )
endif()

set(MOD_DEPS
  Fw/Logger
)
register_fprime_module()
