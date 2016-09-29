#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <fstream>
#include <stdio.h>

#include "Noticia.h"
#include "ItemAgrupableMock.h"

using testing::StrEq;
using testing::SizeIs;
using testing::UnorderedElementsAre;
using testing::Return;
using testing::Throw;

EntidadNombrada findEntidadNombradaByName(std::list<EntidadNombrada> entidades, std::string name);

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

TEST_F(NoticiaTest, givenNoticiaWithoutEntidadNombrada_whenCallingGetMasFrecuente_thenThrowsNoEntidadNomradaException) {
   Noticia n("Titulo de noticia", "la noticia no nombra ninguna entidad", "");

   ASSERT_THROW(n.getMasFrecuente(), NoEntidadNombradaException);
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

TEST_F(NoticiaTest, givenNoticiaWithBlockedWordsList_whenCallingGetPalabrasReservadas_thenListContainsTheBlockedWords) {
   Noticia n("Titulo de noticia", "EntidadExcluida no deberia aparecer", STOP_LIST_FILENAME);

   std::list<std::string> blockedWords = n.getPalabrasReservadas();
   ASSERT_THAT(blockedWords, UnorderedElementsAre("EntidadExcluida"));
}

TEST_F(NoticiaTest, givenNoticiaWithBlockedEntidadNombrada_whenCallingGetEntidades_thenListIsEmpty) {
   Noticia n("Titulo de noticia", "EntidadExcluida no deberia aparecer", STOP_LIST_FILENAME);

   std::list<EntidadNombrada> entidades = n.getEntidades();
   ASSERT_THAT(entidades, SizeIs(0));
}

TEST_F(NoticiaTest, givenNoticiaWithBlockedEntidadNombrada_whenCallingGetMasFrecuente_thenThrowsNoEntidadNombradaException) {
   Noticia n("Titulo de noticia", "EntidadExcluida no deberia aparecer", STOP_LIST_FILENAME);

   ASSERT_THROW(n.getMasFrecuente(), NoEntidadNombradaException);
}

TEST_F(NoticiaTest, givenNoticiaWithSeveralEntidadNombradaOneBlocked_whenCallingGetEntidades_thenBlockedDoesNotShowUp) {
   Noticia n("Titulo de noticia", "EntidadExcluida palabra EntidadExcluida palabra \
                                   EntidadExcluida palabra Entidad1 Entidad1 Entidad2", STOP_LIST_FILENAME);

   std::list<EntidadNombrada> entidades = n.getEntidades();

   ASSERT_THAT(entidades, SizeIs(2));

   std::list<std::string> entidadesStringList;
   for(EntidadNombrada entidad : entidades) {
      entidadesStringList.push_back(entidad.getEntidadNombrada());
   }
   ASSERT_THAT(entidadesStringList, UnorderedElementsAre("Entidad1", "Entidad2"));
}

TEST_F(NoticiaTest, givenNoticiaWithSeveralEntidadNombradaOneBlocked_whenCallingGetMasFrecuente_thenTheBlockedIsNotReturned) {
   Noticia n("Titulo de noticia", "EntidadExcluida palabra EntidadExcluida palabra \
                                   EntidadExcluida palabra Entidad1 Entidad1 Entidad2", STOP_LIST_FILENAME);

   EntidadNombrada mostFrequent = n.getMasFrecuente();

   ASSERT_THAT(mostFrequent.getEntidadNombrada(), StrEq("Entidad1"));
}

TEST_F(NoticiaTest, givenNoticiaWithBlockedEntidadNombrada_whenCallingGetEntidadesRelevantes_thenListIsEmpty) {
   Noticia n("Titulo de noticia", "EntidadExcluida no deberia aparecer", STOP_LIST_FILENAME);

   std::list<EntidadNombrada> entidades = n.getEntidadesRelevantes();
   ASSERT_THAT(entidades, SizeIs(0));
}

TEST_F(NoticiaTest, givenNoticiaWithNoEntidadNombrada_whenCallingEsAgrupablePorEntidad_thenReturnsFalse) {
   Noticia noticiaUnderTest("Titulo de noticia", "noticia sin entidades", "");

   ItemAgrupableMock noticiaMock;

   ASSERT_FALSE(noticiaUnderTest.esAgrupablePorEntidadMasNombrada(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticiaWithEntidadNombrada_whenCallinEsAgrupablePorEntidadWithItemWithNoEntidadNombrada_thenReturnsFalse_) {
   Noticia noticiaUnderTest("Titulo de noticia", "noticia nombra Entidad1", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getMasFrecuente()).WillRepeatedly(Throw(NoEntidadNombradaException()));

   ASSERT_FALSE(noticiaUnderTest.esAgrupablePorEntidadMasNombrada(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticiaWithNoEntidadNombrada_whenCallinEsAgrupablePorEntidadWithItemWithNoEntidadNombrada_thenReturnsFalse) {
   Noticia noticiaUnderTest("Titulo de noticia", "noticia sin entidades", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getMasFrecuente()).WillRepeatedly(Throw(NoEntidadNombradaException()));

   ASSERT_FALSE(noticiaUnderTest.esAgrupablePorEntidadMasNombrada(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_whenCallingEsAgrupablePorEntidadWithItemWithTheSameEntidadMasFrecuente_thenReturnsTrue) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "la EntidadNombrada1 primero, la EntidadNombrada2 segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego la EntidadNombrada3 dos veces: EntidadNombrada3", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getMasFrecuente()).WillRepeatedly(Return(EntidadNombrada("EntidadNombrada1", 6)));

   ASSERT_TRUE(noticiaUnderTest.esAgrupablePorEntidadMasNombrada(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_whenCallingEsAgrupablePorEntidadWithItemWithDifferentEntidadMasFrecuente_thenReturnsFalse) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "la EntidadNombrada1 primero, la EntidadNombrada2 segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego la EntidadNombrada3 dos veces: EntidadNombrada3", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getMasFrecuente()).WillRepeatedly(Return(EntidadNombrada("EntidadNombradaDistinta", 6)));

   ASSERT_FALSE(noticiaUnderTest.esAgrupablePorEntidadMasNombrada(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_whenCallingEntidadMasNombradaEstaEnDestacadoDeItemThatContainsTheEntidad_thenReturnsTrue) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "la EntidadNombrada1 primero, la EntidadNombrada2 segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego la EntidadNombrada3 dos veces: EntidadNombrada3", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getTextoDestacado()).WillRepeatedly(Return("Titulo que contiene EntidadNombrada1"));

   ASSERT_TRUE(noticiaUnderTest.entidadMasNombradaEstaEnDestacadoDe(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_whenCallingEntidadMasNombradaEstaEnDestacadoDeItemThatDoesNotContainTheEntidad_thenReturnsTrue) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "la EntidadNombrada1 primero, la EntidadNombrada2 segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego la EntidadNombrada3 dos veces: EntidadNombrada3", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getTextoDestacado()).WillRepeatedly(Return("Titulo que no contiene la entidad"));

}

TEST_F(NoticiaTest, givenNoticiaWithNoEntidadNombrada_whenCallinEntidadMasNombradaEstaEnDestacadoDeItem_thenReturnsFalse) {
   Noticia noticiaUnderTest("Titulo de noticia", "noticia sin entidades", "");

   ItemAgrupableMock noticiaMock;

   ASSERT_FALSE(noticiaUnderTest.entidadMasNombradaEstaEnDestacadoDe(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_whenCallingEntidadesRelevantesAparecenEnItemThatContains25percentOfTheEntidades_thenReturnsFalse) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "EntidadNombrada1 , EntidadNombrada2 segundo, \
                             EntidadNombrada3 , y EntidadNombrada4. \
                             las cuatro entidades son relevantes, porque aparecen \
                             al principio, para eso estamos metiendo texto de relleno.\
                             con esto estamos seguros de que son relevantes. Habra una \
                             quinta entidad, que no sera relevante: Entidad5", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>({
      EntidadNombrada("EntidadNombrada1", 1)
   })));

   ASSERT_FALSE(noticiaUnderTest.entidadesRelevantesAparecenEn(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_whenCallingEntidadesRelevantesAparecenEnWithItemThatContains25percentOfTheEntidadesOneIsIrrelevant_thenReturnsFalse) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "EntidadNombrada1 , EntidadNombrada2 segundo, \
                             EntidadNombrada3 , y EntidadNombrada4. \
                             las cuatro entidades son relevantes, porque aparecen \
                             al principio, para eso estamos metiendo texto de relleno.\
                             con esto estamos seguros de que son relevantes. Habra una \
                             quinta entidad, que no sera relevante: Entidad5", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>({
      EntidadNombrada("EntidadNombrada1", 1),
      EntidadNombrada("Entidad5", 1)
   })));

   ASSERT_FALSE(noticiaUnderTest.entidadesRelevantesAparecenEn(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_whenCallingEntidadesRelevantesAparecenEnItemThatContains50percentOfTheEntidadRelevante_thenReturnsTrue) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "EntidadNombrada1 , EntidadNombrada2 segundo, \
                             EntidadNombrada3 , y EntidadNombrada4. \
                             las cuatro entidades son relevantes, porque aparecen \
                             al principio, para eso estamos metiendo texto de relleno.\
                             con esto estamos seguros de que son relevantes. Habra una \
                             quinta entidad, que no sera relevante: Entidad5", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>({
      EntidadNombrada("EntidadNombrada1", 1),
      EntidadNombrada("EntidadNombrada3", 1)
   })));

   ASSERT_TRUE(noticiaUnderTest.entidadesRelevantesAparecenEn(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_whenCallingEntidadesRelevantesAparecenEnItemThatDoesNotContainEntidadNombrada_thenReturnsFalse) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "la EntidadNombrada1 primero, la EntidadNombrada2 segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego la EntidadNombrada3 dos veces: EntidadNombrada3", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>()));

   ASSERT_FALSE(noticiaUnderTest.entidadesRelevantesAparecenEn(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_whenCallingEntidadesRelevantesAparecenEnItemThatDoesNotContainRelevantEntidadNombrada_thenReturnsFalse) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "la EntidadNombrada1 primero, segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego lados veces: EntidadNombrada3", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>({
      EntidadNombrada("EntidadNombrada3", 1)
   })));

   ASSERT_FALSE(noticiaUnderTest.entidadesRelevantesAparecenEn(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_WhenCallingEsAgrupablePorTemaWithItemWithNoEntidadMasNombradaInDestacadoAndNoEntidadesRelevantes_thenReturnFalse) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "la EntidadNombrada1 primero, segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego lados veces: EntidadNombrada3", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getTextoDestacado()).WillRepeatedly(Return("Titulo que no contiene la entidad"));
   EXPECT_CALL(noticiaMock, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>({
      EntidadNombrada("EntidadNombrada3", 1)
   })));

   ASSERT_FALSE(noticiaUnderTest.esAgrupablePorTematica(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_WhenCallingEsAgrupablePorTemaWithItemWithEntidadesRelevantesAndNoEntidadMasNombradaInDestacado_thenReturnFalse) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "la EntidadNombrada1 primero, segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego lados veces: EntidadNombrada3", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getTextoDestacado()).WillRepeatedly(Return("Titulo que no contiene la entidad"));
   EXPECT_CALL(noticiaMock, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>({
      EntidadNombrada("EntidadNombrada1", 1)
   })));

   ASSERT_FALSE(noticiaUnderTest.esAgrupablePorTematica(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_WhenCallingEsAgrupablePorTemaWithItemWithEntidadMasNombradaInDestacadoAndNoEntidadesRelevantes_thenReturnFalse) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "la EntidadNombrada1 primero, segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego lados veces: EntidadNombrada3", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getTextoDestacado()).WillRepeatedly(Return("Titulo contiene la EntidadNombrada1"));
   EXPECT_CALL(noticiaMock, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>({
      EntidadNombrada("EntidadNombrada3", 1)
   })));

   ASSERT_FALSE(noticiaUnderTest.esAgrupablePorTematica(noticiaMock));
}

TEST_F(NoticiaTest, givenNoticia_WhenCallingEsAgrupablePorTemaWithItemWithEntidadMasNombradaInDestacadoAndEntidadesRelevantes_thenReturnTrue) {
   Noticia noticiaUnderTest("Titulo de noticia",
                            "la EntidadNombrada1 primero, segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego lados veces: EntidadNombrada3", "");

   ItemAgrupableMock noticiaMock;
   EXPECT_CALL(noticiaMock, getTextoDestacado()).WillRepeatedly(Return("Titulo que no contiene la EntidadNombrada1"));
   EXPECT_CALL(noticiaMock, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>({
      EntidadNombrada("EntidadNombrada1", 1)
   })));

   ASSERT_TRUE(noticiaUnderTest.esAgrupablePorTematica(noticiaMock));
}
