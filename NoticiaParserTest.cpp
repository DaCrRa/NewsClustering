/*
 * NoticiaParserTest.cpp
 *
 *  Created on: 26 de sept. de 2016
 *      Author: dancre
 */

#include <gmock/gmock.h>

#include "Noticia.h"
#include "NoticiaParser.h"

#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>

using testing::StrEq;
using testing::ElementsAre;

class NoticiaParserTest : public ::testing::Test {
public:
   static const std::string STOP_LIST_FILENAME;
protected:
   static void SetUpTestCase() {
      std::ofstream stopList(STOP_LIST_FILENAME);
      stopList << "EntidadExcluida" << std::endl;
   }

   static void TearDownTestCase() {
      remove(STOP_LIST_FILENAME.c_str());
   }
};
const std::string NoticiaParserTest::STOP_LIST_FILENAME = "stopList.txt";

TEST_F(NoticiaParserTest, givenParser_whenCallingParse_thenReturnsNoticiaInstance) {
	std::string noticia("Esto es el titulo de la noticia\n"\
			            "Esto es el primer parrafo del cuerpo de la noticia.\n"\
			            "Esto es la segunda frase del cuerpo de la noticia");

	NoticiaParser parser(std::stringstream(noticia), "stopList.txt");

	Noticia parsedNoticia = parser.parse();

	ASSERT_THAT(parsedNoticia.getTitulo(), StrEq("Esto es el titulo de la noticia"));
	ASSERT_THAT(parsedNoticia.getCuerpo(), StrEq("Esto es el primer parrafo del cuerpo de la noticia.\n"\
			                                     "Esto es la segunda frase del cuerpo de la noticia"));
	ASSERT_THAT(parsedNoticia.getPalabrasReservadas(), ElementsAre("EntidadExcluida"));
}
