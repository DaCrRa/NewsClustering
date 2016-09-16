#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Noticia.h"

using testing::StrEq;

TEST(NoticiaTest, givenNoticiaWithOneEntidadNombrada_whenCallingGetMasFrecuente_thenEntidadNombradaIsReturned) {
   //Noticia n("Titulo de noticia", "la noticia tiene una EntidadNombrada", "");

   //EntidadNombrada entidad = n.getMasFrecuente();
   ASSERT_THAT("EntidadNombrada no ", StrEq("EntidadNombrada"));
}

