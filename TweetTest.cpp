#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <fstream>
#include <stdio.h>

#include "Tweet.h"
#include "ItemAgrupableMock.h"

using testing::StrEq;
using testing::SizeIs;
using testing::UnorderedElementsAre;
using testing::Return;
using testing::Throw;

EntidadNombrada findEntidadNombradaByName(std::list<EntidadNombrada> entidades, std::string name);

class TweetTest : public ::testing::Test {
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
const std::string TweetTest::STOP_LIST_FILENAME = "stopList.txt";

TEST_F(TweetTest, givenTweetWithoutEntidadNombrada_whenCallingGetEntidades_thenListIsEmpty) {
   Tweet t(0, "@pepe_perez", "tweet sin entidades", "");

   std::list<EntidadNombrada> entidades = t.getEntidades();

   ASSERT_THAT(entidades, SizeIs(0));
}

TEST_F(TweetTest, givenTweetWithSeveralDifferentEntidadNombrada_whenCallingGetEntidades_thenAllEntidadesAreInTheList) {
   Tweet t(0, "@pepe_perez", "tuit con Entidad1 Entidad2 Entidad3 y Entidad1", "");

   std::list<EntidadNombrada> entidades = t.getEntidades();

   std::list<std::string> entidadesStringList;
   for(EntidadNombrada entidad : entidades) {
      entidadesStringList.push_back(entidad.getEntidadNombrada());
   }

   ASSERT_THAT(entidades, SizeIs(3));
   ASSERT_THAT(entidadesStringList, UnorderedElementsAre("Entidad1", "Entidad2", "Entidad3"));
}

TEST_F(TweetTest, givenTweetWithSeveralRepeatedEntidadNombrada_whenCallingGetEntidades_thenAllEntidadesAreInTheListWithFrequenciesSet) {
   Tweet t(0, "@pepe_perez", "la EntidadNombrada1 primero, la EntidadNombrada2 segundo, \
              otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
              luego la EntidadNombrada3 dos veces: EntidadNombrada3", "");

   std::list<EntidadNombrada> entidades = t.getEntidades();

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

TEST_F(TweetTest, givenTweetWithSeveralEntidadNombrada_whenCallingGetMasFrecuente_thenReturnsEntidadNombradaWithMoreOccurrences) {
   Tweet t(0, "@pepe_perez", "texto texto EntidadNombradaMasFrecuente EntidadNombradaMasFrecuente \
                                   mas texto EndidadMenosFrequente texto final", "");

   EntidadNombrada entidad = t.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombradaMasFrecuente"));
}

TEST_F(TweetTest, givenTweetWithOneEntidadNombradaInBetween_whenCallingGetMasFrecuente_thenEntidadNombradaIsReturned) {
   Tweet t(0, "@pepe_perez", "la noticia tiene una EntidadNombrada en medio", "");

   EntidadNombrada entidad = t.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombrada"));
   ASSERT_EQ(1, entidad.getFrecuencia());
}

TEST_F(TweetTest, givenTweetWithOneEntidadNombradaAtBegining_whenCallingGetMasFrecuente_thenEntidadNombradaIsReturned) {
   Tweet t(0, "@pepe_perez", "EntidadNombrada al principio de la noticia", "");

   EntidadNombrada entidad = t.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombrada"));
   ASSERT_EQ(1, entidad.getFrecuencia());
}

TEST_F(TweetTest, givenTweetWithOneEntidadNombradaAtTheEnd_whenCallingGetMasFrecuente_thenEntidadNombradaIsReturned) {
   Tweet t(0, "@pepe_perez", "la noticia tiene una EntidadNombrada", "");

   EntidadNombrada entidad = t.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombrada"));
   ASSERT_EQ(1, entidad.getFrecuencia());
}

TEST_F(TweetTest, givenTweetWithoutEntidadNombrada_whenCallingGetMasFrecuente_thenThrowsNoEntidadNomradaException) {
   Tweet t(0, "@pepe_perez", "la noticia no nombra ninguna entidad", "");

   ASSERT_THROW(t.getMasFrecuente(), NoEntidadNombradaException);
}

TEST_F(TweetTest, givenTweetWithBlockedEntidadNombrada_whenCallingGetEntidades_thenListIsEmpty) {
   Tweet t(0, "@pepe_perez", "EntidadExcluida no deberia aparecer", STOP_LIST_FILENAME);

   std::list<EntidadNombrada> entidades = t.getEntidades();
   ASSERT_THAT(entidades, SizeIs(0));
}

TEST_F(TweetTest, givenTweetWithBlockedEntidadNombrada_whenCallingGetMasFrecuente_thenThrowsNoEntidadNombradaException) {
   Tweet t(0, "@pepe_perez", "EntidadExcluida no deberia aparecer", STOP_LIST_FILENAME);

   ASSERT_THROW(t.getMasFrecuente(), NoEntidadNombradaException);
}

TEST_F(TweetTest, givenTweetWithSeveralEntidadNombradaOneBlocked_whenCallingGetEntidades_thenBlockedDoesNotShowUp) {
   Tweet t(0, "@pepe_perez", "EntidadExcluida palabra EntidadExcluida palabra \
                                   EntidadExcluida palabra Entidad1 Entidad1 Entidad2", STOP_LIST_FILENAME);

   std::list<EntidadNombrada> entidades = t.getEntidades();

   ASSERT_THAT(entidades, SizeIs(2));

   std::list<std::string> entidadesStringList;
   for(EntidadNombrada entidad : entidades) {
      entidadesStringList.push_back(entidad.getEntidadNombrada());
   }
   ASSERT_THAT(entidadesStringList, UnorderedElementsAre("Entidad1", "Entidad2"));
}

TEST_F(TweetTest, givenTweetWithSeveralEntidadNombradaOneBlocked_whenCallingGetMasFrecuente_thenTheBlockedIsNotReturned) {
   Tweet t(0, "@pepe_perez", "EntidadExcluida palabra EntidadExcluida palabra \
                                   EntidadExcluida palabra Entidad1 Entidad1 Entidad2", STOP_LIST_FILENAME);

   EntidadNombrada mostFrequent = t.getMasFrecuente();

   ASSERT_THAT(mostFrequent.getEntidadNombrada(), StrEq("Entidad1"));
}

TEST_F(TweetTest, givenTweetWithNoEntidadNombrada_whenCallingEsAgrupablePorEntidad_thenReturnsFalse) {
   Tweet t(0, "@pepe_perez",  "noticia sin entidades", "");

   ItemAgrupableMock item;

   ASSERT_FALSE(t.esAgrupablePorEntidadMasNombrada(item));
}

TEST_F(TweetTest, givenTweetWithEntidadNombrada_whenCallinEsAgrupablePorEntidadWithItemWithNoEntidadNombrada_thenReturnsFalse_) {
   Tweet t(0, "@pepe_perez",  "noticia nombra Entidad1", "");

   ItemAgrupableMock item;
   EXPECT_CALL(item, getMasFrecuente()).WillRepeatedly(Throw(NoEntidadNombradaException()));

   ASSERT_FALSE(t.esAgrupablePorEntidadMasNombrada(item));
}

TEST_F(TweetTest, givenTweetWithNoEntidadNombrada_whenCallinEsAgrupablePorEntidadWithItemWithNoEntidadNombrada_thenReturnsFalse) {
   Tweet t(0, "@pepe_perez", "noticia sin entidades", "");

   ItemAgrupableMock item;
   EXPECT_CALL(item, getMasFrecuente()).WillRepeatedly(Throw(NoEntidadNombradaException()));

   ASSERT_FALSE(t.esAgrupablePorEntidadMasNombrada(item));
}

TEST_F(TweetTest, givenTweet_whenCallingEsAgrupablePorEntidadWithItemWithTheSameEntidadMasFrecuente_thenReturnsTrue) {
   Tweet t(0, "@pepe_perez", "la EntidadNombrada1 primero, la EntidadNombrada2 segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego la EntidadNombrada3 dos veces: EntidadNombrada3", "");

   ItemAgrupableMock item;
   EXPECT_CALL(item, getMasFrecuente()).WillRepeatedly(Return(EntidadNombrada("EntidadNombrada1", 6)));

   ASSERT_TRUE(t.esAgrupablePorEntidadMasNombrada(item));
}

TEST_F(TweetTest, givenTweet_whenCallingEsAgrupablePorEntidadWithItemWithDifferentEntidadMasFrecuente_thenReturnsFalse) {
   Tweet t(0, "@pepe_perez", "la EntidadNombrada1 primero, la EntidadNombrada2 segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego la EntidadNombrada3 dos veces: EntidadNombrada3", "");

   ItemAgrupableMock item;
   EXPECT_CALL(item, getMasFrecuente()).WillRepeatedly(Return(EntidadNombrada("EntidadNombradaDistinta", 6)));

   ASSERT_FALSE(t.esAgrupablePorEntidadMasNombrada(item));
}

TEST_F(TweetTest, givenTweet_WhenCallingEsAgrupablePorTemaWithItemWithNoEntidadNombrada_thenReturnFalse) {
   Tweet t(0, "@pepe_perez", "la EntidadNombrada1 primero, segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego lados veces: EntidadNombrada3", "");

   ItemAgrupableMock item;
   EXPECT_CALL(item, getTextoDestacado()).WillRepeatedly(Return("titulo que no contiene la entidad"));
   EXPECT_CALL(item, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>()));

   ASSERT_FALSE(t.esAgrupablePorTematica(item));
}

TEST_F(TweetTest, givenTweetContainingEntidadMasNombradaOfAnItem_WhenCallingEsAgrupablePorTemaWithItem_thenReturnTrue) {
   Tweet t(0, "@pepe_perez", "la EntidadNombrada1 primero, segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego lados veces: EntidadNombrada3", "");

   ItemAgrupableMock item;
   EXPECT_CALL(item, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>({
      EntidadNombrada("EntidadNombrada3", 1)
   })));

   ASSERT_TRUE(t.esAgrupablePorTematica(item));
}

TEST_F(TweetTest, givenTweetContainingEntidadNoMasNombradaOfItem_WhenCallingEsAgrupablePorTemaWithItem_thenReturnFalse) {
   Tweet t(0, "@pepe_perez", "la EntidadNombrada1 primero, segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego lados veces: EntidadNombrada3", "");

   ItemAgrupableMock item;
   EXPECT_CALL(item, getEntidades()).WillRepeatedly(Return(std::list<EntidadNombrada>({
      EntidadNombrada("OtraEntidad", 1)
   })));

   ASSERT_FALSE(t.esAgrupablePorTematica(item));
}

TEST_F(TweetTest, givenTweet_WhenCallingEsAgrupablePorTemaWithItemSharingEntity_thenReturnTrue) {
   Tweet t(0, "@pepe_perez", "la EntidadNombrada1 primero, segundo, \
                             otra vez la EntidadNombrada1 , de nuevo EntidadNombrada1 , \
                             luego lados veces: EntidadNombrada3", "");

   ItemAgrupableMock item;
   FAIL() << "need to add some funtions to Item interface";
}
