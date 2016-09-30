cmake_minimum_required(VERSION 2.8)
project(NewsClustering)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

#add_subdirectory(src)
#add_subdirectory(test)

include(jsoncpp.cmake)

set(analyzer_source_files
#   ${JSONCPP_SRC_FILE}
   AbstractItemAgrupable.cpp
   EntidadNombrada.cpp
   AgrupadorDeGrupos.cpp
   AgrupadorDeItems.cpp
   PorTematica.cpp
   PorEntidadMasNombrada.cpp
)
add_library(Analyzer SHARED ${analyzer_source_files})

set(tweetparser_source_files
   Tweet.cpp
)
add_library(TweetParser SHARED ${tweetparser_source_files})
target_link_libraries(TweetParser Analyzer stdc++fs)

set(noticiaparser_source_files
   Noticia.cpp
   NoticiaParser.cpp
   NoticiaFolderReader.cpp
)
add_library(NoticiaParser SHARED ${noticiaparser_source_files})
target_link_libraries(NoticiaParser Analyzer stdc++fs)

add_executable(NewsClustering "Main.cpp")
target_link_libraries(NewsClustering Analyzer NoticiaParser)

include(googletest.cmake)

set(test_source_files
   EntidadNombradaTest.cpp
   NoticiaTest.cpp
   TweetTest.cpp
   AgrupadorDeItemsTest.cpp
   AgrupadorDeGruposTest.cpp
   PorEntidadMasNombradaTest.cpp
   PorTematicaTest.cpp
   NoticiaParserTest.cpp
   FindEntidadMasNombradaByNameFunc.cpp
   NoticiaTweetGrouping.cpp
   TweetGroupingTest.cpp
)
build_googletest_executable(NewsClusteringTest
   "${test_source_files}"
   "Analyzer;NoticiaParser;TweetParser"
)
