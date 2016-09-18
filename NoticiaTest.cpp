#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <fstream>
#include <stdio.h>

#include "Noticia.h"

using testing::StrEq;
using testing::SizeIs;
using testing::UnorderedElementsAre;

EntidadNombrada findEntidadNombradaByName(std::list<EntidadNombrada> entidades, std::string name) {
    auto it = std::find_if( std::begin(entidades),
                            std::end(entidades),
                            [&](const EntidadNombrada e){ return e.getEntidadNombrada().compare(name) == 0; } );
    return *it;
}

class NoticiaTest : public ::testing::Test {
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
const std::string NoticiaTest::STOP_LIST_FILENAME = "stopList.txt";

TEST_F(NoticiaTest, givenNoticiaWithoutEntidadNombrada_whenCallingGetEntidades_thenListIsEmpty) {
   Noticia n("Titulo de noticia", "la noticia no nombra nada", "");

   std::list<EntidadNombrada> entidades = n.getEntidades();

   ASSERT_THAT(entidades, SizeIs(0));
}

TEST_F(NoticiaTest, givenNoticiaWithSeveralDifferentEntidadNombrada_whenCallingGetEntidades_thenAllEntidadesAreInTheList) {
   Noticia n("Titulo de noticia", "la EntidadNombrada1 primero, la EntidadNombrada2 segundo, \
                                   luego la EntidadNombrada3", "");

   std::list<EntidadNombrada> entidades = n.getEntidades();

   std::list<std::string> entidadesStringList;
   for(EntidadNombrada entidad : entidades) {
      entidadesStringList.push_back(entidad.getEntidadNombrada());
   }

   ASSERT_THAT(entidades, SizeIs(3));
   ASSERT_THAT(entidadesStringList, UnorderedElementsAre("EntidadNombrada1", "EntidadNombrada2", "EntidadNombrada3"));
}

TEST_F(NoticiaTest, givenNoticiaWithSeveralRepeatedEntidadNombrada_whenCallingGetEntidades_thenAllEntidadesAreInTheListWithFrequenciesSet) {
   Noticia n("Titulo de noticia",
             "la EntidadNombrada1 primero, la EntidadNombrada2 segundo, \
              otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
              luego la EntidadNombrada3 dos veces: EntidadNombrada3", "");

   std::list<EntidadNombrada> entidades = n.getEntidades();

   std::list<std::string> entidadesStringList;
   for(EntidadNombrada entidad : entidades) {
      entidadesStringList.push_back(entidad.getEntidadNombrada());
   }

   ASSERT_THAT(entidades, SizeIs(3));

   EntidadNombrada entidad1 = findEntidadNombradaByName(entidades, "EntidadNombrada1");
   ASSERT_THAT(entidad1.getEntidadNombrada(), StrEq("EntidadNombrada1"));
   ASSERT_EQ(3, entidad1.getFrecuencia());

   EntidadNombrada entidad2 = findEntidadNombradaByName(entidades, "EntidadNombrada2");
   ASSERT_THAT(entidad2.getEntidadNombrada(), StrEq("EntidadNombrada2"));
   ASSERT_EQ(1, entidad2.getFrecuencia());

   EntidadNombrada entidad3 = findEntidadNombradaByName(entidades, "EntidadNombrada3");
   ASSERT_THAT(entidad3.getEntidadNombrada(), StrEq("EntidadNombrada3"));
   ASSERT_EQ(2, entidad3.getFrecuencia());
}

TEST_F(NoticiaTest, givenNoticiaWithSeveralEntidadNombrada_whenCallingGetMasFrecuente_thenReturnsEntidadNombradaWithMoreOccurrences) {
   Noticia n("Titulo de noticia", "texto texto EntidadNombradaMasFrecuente EntidadNombradaMasFrecuente \
                                   mas texto EndidadMenosFrequente texto final", "");

   EntidadNombrada entidad = n.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombradaMasFrecuente"));
}

TEST_F(NoticiaTest, givenNoticiaWithOneEntidadNombradaInBetween_whenCallingGetMasFrecuente_thenEntidadNombradaIsReturned) {
   Noticia n("Titulo de noticia", "la noticia tiene una EntidadNombrada en medio", "");

   EntidadNombrada entidad = n.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombrada"));
   ASSERT_EQ(1, entidad.getFrecuencia());
}

TEST_F(NoticiaTest, givenNoticiaWithOneEntidadNombradaAtBegining_whenCallingGetMasFrecuente_thenEntidadNombradaIsReturned) {
   Noticia n("Titulo de noticia", "EntidadNombrada al principio de la noticia", "");

   EntidadNombrada entidad = n.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombrada"));
   ASSERT_EQ(1, entidad.getFrecuencia());
}

TEST_F(NoticiaTest, givenNoticiaWithOneEntidadNombradaAtTheEnd_whenCallingGetMasFrecuente_thenEntidadNombradaIsReturned) {
   Noticia n("Titulo de noticia", "la noticia tiene una EntidadNombrada", "");

   EntidadNombrada entidad = n.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombrada"));
   ASSERT_EQ(1, entidad.getFrecuencia());
}

TEST_F(NoticiaTest, givenNoticiaWithoutEntidadNombrada_whenCallingGetMasFrecuente_thenItsFrecuenciaIsZero) {
   Noticia n("Titulo de noticia", "la noticia no nombra ninguna entidad", "");

   EntidadNombrada entidad = n.getMasFrecuente();
   ASSERT_EQ(0, entidad.getFrecuencia());
}

TEST_F(NoticiaTest, givenNoticiaWithEntidadNombradaNoRelevant_whenCallingGetEntidadesRelevantes_thenListIsEmpty) {
   Noticia n("Titulo de noticia", "esta entidad nombrada no es relevante: Entidad1", "");

   std::list<EntidadNombrada> entidadesRelevantes = n.getEntidadesRelevantes();
   ASSERT_THAT(entidadesRelevantes, SizeIs(0));
}

TEST_F(NoticiaTest, givenNoticiaWithEntidadNombradaRelevant_whenCallingGetEntidadesRelevantes_thenEntidadIsInTheList) {
   Noticia n("Titulo de noticia", "Entidad1 es relevante porque va al principio", "");

   std::list<EntidadNombrada> entidadesRelevantes = n.getEntidadesRelevantes();
   ASSERT_THAT(entidadesRelevantes, SizeIs(1));
   ASSERT_THAT(entidadesRelevantes.begin()->getEntidadNombrada(), StrEq("Entidad1"));
   ASSERT_EQ(1, entidadesRelevantes.begin()->getFrecuencia());
}

TEST_F(NoticiaTest, givenNoticiaWithEntidadNombradaRelevantMentionedTwice_whenCallingGetEntidadesRelevantes_thenEntidadIsInTheList) {
   Noticia n("Titulo de noticia", "Entidad1 es relevante porque va al principio, pero tambien al final Entidad1", "");

   std::list<EntidadNombrada> entidadesRelevantes = n.getEntidadesRelevantes();
   ASSERT_THAT(entidadesRelevantes, SizeIs(1));
   ASSERT_THAT(entidadesRelevantes.begin()->getEntidadNombrada(), StrEq("Entidad1"));
   ASSERT_EQ(2, entidadesRelevantes.begin()->getFrecuencia());
}

TEST_F(NoticiaTest, givenNoticiaWithThreeEntidadNombradaOneRelevant_whenCallingGetEntidadesRelevantes_thenEntidadRelevanteIsInTheList) {
   Noticia n("Titulo de noticia", "Entidad1 es relevante porque va al principio. \
                                   Entidad2 y Entidad3 no. Entidad1", "");

   std::list<EntidadNombrada> entidadesRelevantes = n.getEntidadesRelevantes();
   ASSERT_THAT(entidadesRelevantes, SizeIs(1));
   ASSERT_THAT(entidadesRelevantes.begin()->getEntidadNombrada(), StrEq("Entidad1"));
   ASSERT_EQ(2, entidadesRelevantes.begin()->getFrecuencia());
}
