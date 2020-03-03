####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
if(${CMAKE_SYSTEM_NAME} STREQUAL "AVR")
  set(SOURCE_FILES "${SOURCE_FILES}"
    "${CMAKE_CURRENT_LIST_DIR}/AVRTimeImpl.cpp"
  )
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  set(SOURCE_FILES "${SOURCE_FILES}"
    "${CMAKE_CURRENT_LIST_DIR}/DarwinTimeImpl.cpp"
  )
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "VxWorks")
  set(SOURCE_FILES "${SOURCE_FILES}"
    "${CMAKE_CURRENT_LIST_DIR}/VxWorksTimeImpl.cpp"
  )
else()
  set(SOURCE_FILES "${SOURCE_FILES}"
    "${CMAKE_CURRENT_LIST_DIR}/LinuxTimeImpl.cpp"
  )
endif()

set(MOD_DEPS
  Svc/Time
)

register_fprime_module()
### UTs ###
set(UT_SOURCE_FILES
  "${FPRIME_CORE_DIR}/Svc/Time/TimeComponentAi.xml"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Main.cpp"
)
register_fprime_ut()
