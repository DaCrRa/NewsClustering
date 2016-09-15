cmake_minimum_required(VERSION 2.8)
project(NewsClustering)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

#add_subdirectory(src)
#add_subdirectory(test)

set(analyzer_source_files
   Analizador.cpp
   EntidadNombrada.cpp
   Noticia.cpp
)
add_library(Analyzer SHARED ${analyzer_source_files})

add_executable(NewsClustering "Main.cpp")
target_link_libraries(NewsClustering Analyzer)

include(googletest.cmake)

set(test_source_files
   EntidadNombradaTest.cpp
)
build_googletest_executable(NewsClusteringTest ${test_source_files} Analyzer)
