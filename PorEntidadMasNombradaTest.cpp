/*
 * PorEntidadMasNombradaTest.cpp
 *
 *  Created on: 25 de sept. de 2016
 *      Author: dancre
 */

#include <gmock/gmock.h>

#include "PorEntidadMasNombrada.h"
#include "NoticiaIfMock.h"

using testing::Return;
using testing::_;

TEST(PorEntidadMasNombradaTest, givenPorEntidadMasNombrada_whenCallingSonAgrupablesWithTwoNonGroupableNoticias_thenReturnsFalse) {
	std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
	std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
	EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
	EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	NoticiaIfPtr n1(noticia1);
	NoticiaIfPtr n2(noticia2);
	ASSERT_FALSE(criterio->sonAgrupables(n1, n2));
	ASSERT_FALSE(criterio->sonAgrupables(n2, n1));
}

TEST(PorEntidadMasNombradaTest, givenPorEntidadMasNombrada_whenCallingSonAgrupablesWithOneGroupableAndOneNotGroupableNoticia_thenReturnsTrue) {
	std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
	std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
	EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(true));
	EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	NoticiaIfPtr n1(noticia1);
	NoticiaIfPtr n2(noticia2);
	ASSERT_TRUE(criterio->sonAgrupables(n1, n2));
	ASSERT_TRUE(criterio->sonAgrupables(n2, n1));
}

TEST(PorEntidadMasNombradaTest, givenPorEntidadMasNombrada_whenCallingSonAgrupablesWithTwoGroupableNoticia_thenReturnsTrue) {
	std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
	std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
	EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(true));
	EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(true));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	NoticiaIfPtr n1(noticia1);
	NoticiaIfPtr n2(noticia2);
	ASSERT_TRUE(criterio->sonAgrupables(n1, n2));
	ASSERT_TRUE(criterio->sonAgrupables(n2, n1));
}
