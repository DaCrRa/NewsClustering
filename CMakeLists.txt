cmake_minimum_required(VERSION 2.8)
project(NewsClustering)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

#add_subdirectory(src)
#add_subdirectory(test)

set(news_clustering_source_files
   Analizador.cpp
   EntidadNombrada.cpp
   Main.cpp
   Noticia.cpp
)
add_executable(NewsClustering "${news_clustering_source_files}")

include(googletest.cmake)

build_googletest_executable(NewsClusteringTest "Test.cpp;${news_clustering_source_files}" "")
