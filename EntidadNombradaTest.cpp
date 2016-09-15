#include <gtest/gtest.h>

#include "EntidadNombrada.h"

TEST(EntidadNombradaTest, givenEntidadNombrada_whenCallingEsIgualWithItself_thenReturnsTrue) {
   EntidadNombrada e("mi entidad", 0);
   ASSERT_TRUE(e.esIgual(e));
}

TEST(EntidadNombradaTest, givenTwoEntidadNombradaWithSameName_whenCallingEsIgual_thenReturnsTrue) {
   EntidadNombrada e1("mi entidad", 0);
   EntidadNombrada e2("mi entidad", 0);
   ASSERT_TRUE(e1.esIgual(e2));
   ASSERT_TRUE(e2.esIgual(e1));
}

TEST(EntidadNombradaTest, givenTwoEntidadNombradaWithDifferentName_whenCallingEsIgual_thenReturnsFalse) {
   EntidadNombrada e1("mi entidad uno", 0);
   EntidadNombrada e2("mi entidad dos", 0);
   ASSERT_FALSE(e1.esIgual(e2));
   ASSERT_FALSE(e2.esIgual(e1));
}
