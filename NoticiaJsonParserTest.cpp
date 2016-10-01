/*
 * NoticiaParserTest.cpp
 *
 *  Created on: 26 de sept. de 2016
 *      Author: dancre
 */

#include <gmock/gmock.h>

#include "Noticia.h"
#include "NoticiaJsonParser.h"

#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>

using testing::StrEq;
using testing::ElementsAre;

class NoticiaJsonParserTest : public ::testing::Test {
public:
   static const std::string STOP_LIST_FILENAME;
protected:
   static void SetUpTestCase() {
      std::ofstream stopList(STOP_LIST_FILENAME);
      stopList << "EntidadExcluida" << std::endl;

      std::ofstream stopList2("stopList2.txt");
      stopList2 << "EntidadExcluida2" << std::endl;
   }

   static void TearDownTestCase() {
      remove(STOP_LIST_FILENAME.c_str());
      remove("stopList2.txt");
   }
};
const std::string NoticiaJsonParserTest::STOP_LIST_FILENAME = "stopList.txt";

TEST_F(NoticiaJsonParserTest, givenParser_whenCallingParse_thenReturnsNoticiaInstance) {
	std::string noticia(
			"{" \
				"\"titulo\": \"Esto es el titulo de la noticia\","\
			    "\"parrafos\":[ "\
					"\"Esto es el primer parrafo del cuerpo de la noticia.\"," \
			    	"\"Esto es la segunda frase del cuerpo de la noticia\"" \
				"]" \
			"}");

	std::stringstream input(noticia);
	NoticiaJsonParser parser(input, "stopList.txt");

	Noticia parsedNoticia = parser.parse();

	ASSERT_THAT(parsedNoticia.getTitulo(), StrEq("Esto es el titulo de la noticia"));
	ASSERT_THAT(parsedNoticia.getCuerpo(), StrEq("Esto es el primer parrafo del cuerpo de la noticia.\n"\
			                                     "Esto es la segunda frase del cuerpo de la noticia"));
	ASSERT_THAT(parsedNoticia.getPalabrasReservadas(), ElementsAre("EntidadExcluida"));
}

TEST_F(NoticiaJsonParserTest, givenParser_whenCallingParse_thenReturnsNoticiaInstance_2) {
	std::string noticia(
				"{" \
					"\"titulo\": \"Esto es el titulo de la segunda noticia\","\
				    "\"parrafos\":[ "\
						"\"Esto es el primer parrafo del cuerpo de la segunda noticia.\"," \
				    	"\"Esto es la segunda frase del cuerpo de la noticia\"" \
					"]" \
				"}");

	std::stringstream input(noticia);
	NoticiaJsonParser parser(input, "stopList2.txt");

	Noticia parsedNoticia = parser.parse();

	ASSERT_THAT(parsedNoticia.getTitulo(), StrEq("Esto es el titulo de la segunda noticia"));
	ASSERT_THAT(parsedNoticia.getCuerpo(), StrEq("Esto es el primer parrafo del cuerpo de la segunda noticia.\n"\
			                                     "Esto es la segunda frase del cuerpo de la noticia"));
	ASSERT_THAT(parsedNoticia.getPalabrasReservadas(), ElementsAre("EntidadExcluida2"));
}

TEST_F(NoticiaJsonParserTest, givenParser_whenCallingParseNoticiaSinCuerpo_thenReturnsNoticiaInstance) {
	std::string noticia(
				"{" \
					"\"titulo\": \"Esto es el titulo de la noticia sin cuerpo\""\
				"}");
	std::stringstream input(noticia);
	NoticiaJsonParser parser(input, "stopList.txt");

	Noticia parsedNoticia = parser.parse();

	ASSERT_THAT(parsedNoticia.getTitulo(), StrEq("Esto es el titulo de la noticia sin cuerpo"));
	ASSERT_THAT(parsedNoticia.getCuerpo(), StrEq(""));
	ASSERT_THAT(parsedNoticia.getPalabrasReservadas(), ElementsAre("EntidadExcluida"));
}

//TEST_F(NoticiaJsonParserTest, givenParser_whenCallingParseNoticiaSinCuerpoWhiteLines_thenReturnsNoticiaInstance) {
//	std::string noticia("\n"\
//			"Esto es el titulo de la noticia sin cuerpo\n"\
//			"      ");
//
//	std::stringstream input(noticia);
//	NoticiaParser parser(input, "stopList.txt");
//
//	Noticia parsedNoticia = parser.parse();
//
//	ASSERT_THAT(parsedNoticia.getTitulo(), StrEq("Esto es el titulo de la noticia sin cuerpo"));
//	ASSERT_THAT(parsedNoticia.getCuerpo(), StrEq(""));
//	ASSERT_THAT(parsedNoticia.getPalabrasReservadas(), ElementsAre("EntidadExcluida"));
//}
//
//TEST_F(NoticiaJsonParserTest, givenParser_whenCallingParseNoticiaWhiteLines_thenReturnsNoticiaInstance) {
//	std::string noticia("\n"\
//			"Esto es el titulo de la noticia con cuerpo\n"\
//			"      \n"\
//			"el cuerpo");
//
//	std::stringstream input(noticia);
//	NoticiaParser parser(input, "stopList.txt");
//
//	Noticia parsedNoticia = parser.parse();
//
//	ASSERT_THAT(parsedNoticia.getTitulo(), StrEq("Esto es el titulo de la noticia con cuerpo"));
//	ASSERT_THAT(parsedNoticia.getCuerpo(), StrEq("el cuerpo"));
//	ASSERT_THAT(parsedNoticia.getPalabrasReservadas(), ElementsAre("EntidadExcluida"));
//}
//
//TEST_F(NoticiaJsonParserTest, givenParser_whenCallingParseNoticiaWithJustWhiteLines_thenThrowsNoticiaInvalidaException) {
//	std::string noticia("     \t\t"\
//			"\n"\
//			"      \n"\
//			"");
//
//	std::stringstream input(noticia);
//	NoticiaParser parser(input, "stopList.txt");
//
//	ASSERT_THROW(parser.parse(), NoticiaInvalidaException);
//}
//
//TEST_F(NoticiaJsonParserTest, givenParser_whenCallingParseNoticiaWithEmptyString_thenThrowsNoticiaInvalidaException) {
//	std::string noticia("");
//
//	std::stringstream input(noticia);
//	NoticiaParser parser(input, "stopList.txt");
//
//	ASSERT_THROW(parser.parse(), NoticiaInvalidaException);
//}
