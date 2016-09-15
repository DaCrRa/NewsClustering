include(ExternalProject)

ExternalProject_Add(googletest
   GIT_REPOSITORY  https://github.com/google/googletest
   GIT_TAG         0a43962
   INSTALL_COMMAND true
)

ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIR "${source_dir}/googletest/include")
set(GMOCK_INCLUDE_DIR "${source_dir}/googlemock/include")

ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBRARY_PATH ${binary_dir}/googlemock/gtest/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
set(GTEST_LIBRARY gtest)

set(GTEST_MAIN_LIBRARY_PATH ${binary_dir}/googlemock/gtest/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a)
set(GTEST_MAIN_LIBRARY gtest_main)

add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)
add_library(${GTEST_MAIN_LIBRARY} UNKNOWN IMPORTED)

set_property(TARGET ${GTEST_MAIN_LIBRARY} PROPERTY IMPORTED_LOCATION
                ${GTEST_MAIN_LIBRARY_PATH} )

set_property(TARGET ${GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION
                ${GTEST_LIBRARY_PATH} )
set_property(TARGET ${GTEST_LIBRARY} PROPERTY INTERFACE_LINK_LIBRARIES
                "${GTEST_MAIN_LIBRARY};pthread" )

add_dependencies(${GTEST_MAIN_LIBRARY} googletest)
add_dependencies(${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

macro(build_googletest_executable executable_name sources dependencies)
   add_executable(${executable_name} ${sources})
   target_include_directories(${executable_name} PRIVATE ${GTEST_INCLUDE_DIR})
   target_link_libraries(${executable_name} gtest)
   if(NOT "${dependecies}" STREQUAL "")
      add_dependencies(${executable_name} ${dependencies})
   endif()
endmacro()
