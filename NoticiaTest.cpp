#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Noticia.h"

using testing::StrEq;

TEST(NoticiaTest, givenNoticiaWithOneEntidadNombradaInBetween_whenCallingGetMasFrecuente_thenEntidadNombradaIsReturned) {
   Noticia n("Titulo de noticia", "la noticia tiene una EntidadNombrada en medio", "");

   EntidadNombrada entidad = n.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombrada"));
}

TEST(NoticiaTest, givenNoticiaWithOneEntidadNombradaAtBegining_whenCallingGetMasFrecuente_thenEntidadNombradaIsReturned) {
   Noticia n("Titulo de noticia", "EntidadNombrada al principio de la noticia", "");

   EntidadNombrada entidad = n.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombrada"));
}

TEST(NoticiaTest, givenNoticiaWithOneEntidadNombradaAtTheEnd_whenCallingGetMasFrecuente_thenEntidadNombradaIsReturned) {
   Noticia n("Titulo de noticia", "la noticia tiene una EntidadNombrada", "");

   EntidadNombrada entidad = n.getMasFrecuente();
   ASSERT_THAT(entidad.getEntidadNombrada(), StrEq("EntidadNombrada"));
}
