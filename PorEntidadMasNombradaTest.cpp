/*
 * PorEntidadMasNombradaTest.cpp
 *
 *  Created on: 25 de sept. de 2016
 *      Author: dancre
 */

#include <gmock/gmock.h>

#include "PorEntidadMasNombrada.h"
#include "ItemAgrupableMock.h"

using testing::Return;
using testing::_;

TEST(PorEntidadMasNombradaTest, givenPorEntidadMasNombrada_whenCallingSonAgrupablesWithTwoNonGroupableItems_thenReturnsFalse) {
	std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
	std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
	EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
	EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr n1(noticia1);
	ItemAgrupablePtr n2(noticia2);
	ASSERT_FALSE(criterio->sonAgrupables(n1, n2));
	ASSERT_FALSE(criterio->sonAgrupables(n2, n1));
}

TEST(PorEntidadMasNombradaTest, givenPorEntidadMasNombrada_whenCallingSonAgrupablesWithOneGroupableAndOneNotGroupableItem_thenReturnsTrue) {
	std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
	std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
	EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(true));
	EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr n1(noticia1);
	ItemAgrupablePtr n2(noticia2);
	ASSERT_TRUE(criterio->sonAgrupables(n1, n2));
	ASSERT_TRUE(criterio->sonAgrupables(n2, n1));
}

TEST(PorEntidadMasNombradaTest, givenPorEntidadMasNombrada_whenCallingSonAgrupablesWithTwoGroupableItem_thenReturnsTrue) {
	std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
	std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
	EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(true));
	EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(true));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr n1(noticia1);
	ItemAgrupablePtr n2(noticia2);
	ASSERT_TRUE(criterio->sonAgrupables(n1, n2));
	ASSERT_TRUE(criterio->sonAgrupables(n2, n1));
}
