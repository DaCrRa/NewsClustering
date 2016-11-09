include(ExternalProject)

find_path(GTEST_INCLUDE_DIR gtest/gtest.h)
find_path(GMOCK_INCLUDE_DIR gmock/gmock.h)

find_library(GTEST_LIBRARY gtest)
find_library(GTEST_MAIN_LIBRARY gtest_main)
find_library(GMOCK_LIBRARY gmock)
find_library(GMOCK_MAIN_LIBRARY gmock_main)

macro(build_googletest_executable executable_name sources dependencies)
   add_executable(${executable_name} ${sources})
   target_include_directories(${executable_name} PRIVATE ${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR})
   target_link_libraries(${executable_name} ${GTEST_LIBRARY}
                                            ${GTEST_MAIN_LIBRARY}
                                            ${GMOCK_LIBRARY}
                                            ${GMOCK_MAIN_LIBRARY}
                                            pthread)
   if(NOT "${dependencies}" STREQUAL "")
      target_link_libraries(${executable_name} ${dependencies})
   endif()
endmacro()
