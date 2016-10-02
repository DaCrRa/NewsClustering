cmake_minimum_required(VERSION 2.8)
project(NewsClustering)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -z defs -std=c++11")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

#add_subdirectory(src)
#add_subdirectory(test)


set(analyzer_source_files
   AbstractItemAgrupable.cpp
   EntidadNombrada.cpp
   AgrupadorDeGrupos.cpp
   AgrupadorDeItems.cpp
   PorTematica.cpp
   PorEntidadMasNombrada.cpp
)
add_library(Analyzer SHARED ${analyzer_source_files})

include(jsoncpp.cmake)
set(jsonparser_sources
   ${JSONCPP_SRC_FILE}
   JsonParser.cpp
)
add_library(JsonParser SHARED ${jsonparser_sources})

set(tweetparser_source_files
   Tweet.cpp
   TweetParser.cpp
)
add_library(TweetParser SHARED ${tweetparser_source_files})
target_link_libraries(TweetParser Analyzer JsonParser stdc++fs)

set(noticiaparser_source_files
   Noticia.cpp
   NoticiaPlainTextParser.cpp
   NoticiaJsonParser.cpp
   NoticiaFolderReader.cpp
)
add_library(NoticiaParser SHARED ${noticiaparser_source_files})
target_link_libraries(NoticiaParser Analyzer JsonParser stdc++fs)

set(groupingserializer_source_files
   ${JSONCPP_SRC_FILE}
   GroupingJsonSerializer.cpp
)
add_library(GroupingSerializer SHARED ${groupingserializer_source_files})
#target_link_libraries(GroupingSerializer Analizer)

add_executable(NewsClustering "Main.cpp")
target_link_libraries(NewsClustering Analyzer NoticiaParser TweetParser)

include(googletest.cmake)

set(test_source_files
   EntidadNombradaTest.cpp
   NoticiaTest.cpp
   TweetTest.cpp
   AgrupadorDeItemsTest.cpp
   AgrupadorDeGruposTest.cpp
   PorEntidadMasNombradaTest.cpp
   PorTematicaTest.cpp
   NoticiaPlainTextParserTest.cpp
   FindEntidadMasNombradaByNameFunc.cpp
   NoticiaTweetGrouping.cpp
   TweetGroupingTest.cpp
   TweetParserTest.cpp
   NoticiaJsonParserTest.cpp
   GroupingJsonSerializerTest.cpp
)
build_googletest_executable(NewsClusteringTest
   "${test_source_files}"
   "Analyzer;NoticiaParser;TweetParser;GroupingSerializer"
)
