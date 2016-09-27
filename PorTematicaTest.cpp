/*
 * PorTematicaTest.cpp
 *
 *  Created on: 25 de sept. de 2016
 *      Author: dancre
 */

#include <gmock/gmock.h>

#include "PorTematica.h"

#include "ItemAgrupableMock.h"

using testing::Return;
using testing::_;

TEST(PorTematicaTest, givenPorTematica_whenCallingSonAgrupablesWithTwoNonGroupableItems_thenReturnsFalse) {
	std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
	std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
	EXPECT_CALL(*noticia1, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
	EXPECT_CALL(*noticia2, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));

	CriterioDeAgrupacionPtr criterio(new PorTematica());

	ItemAgrupablePtr n1(noticia1);
	ItemAgrupablePtr n2(noticia2);
	ASSERT_FALSE(criterio->sonAgrupables(n1, n2));
	ASSERT_FALSE(criterio->sonAgrupables(n2, n1));
}

TEST(PorTematicaTest, givenPorTematica_whenCallingSonAgrupablesWithOneGroupableAndOneNotGroupableItem_thenReturnsTrue) {
	std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
	std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
	EXPECT_CALL(*noticia1, esAgrupablePorTematica(_)).WillRepeatedly(Return(true));
	EXPECT_CALL(*noticia2, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));

	CriterioDeAgrupacionPtr criterio(new PorTematica());

	ItemAgrupablePtr n1(noticia1);
	ItemAgrupablePtr n2(noticia2);
	ASSERT_TRUE(criterio->sonAgrupables(n1, n2));
	ASSERT_TRUE(criterio->sonAgrupables(n2, n1));
}

TEST(PorTematicaTest, givenPorTematica_whenCallingSonAgrupablesWithTwoGroupableItem_thenReturnsTrue) {
	std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
	std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
	EXPECT_CALL(*noticia1, esAgrupablePorTematica(_)).WillRepeatedly(Return(true));
	EXPECT_CALL(*noticia2, esAgrupablePorTematica(_)).WillRepeatedly(Return(true));

	CriterioDeAgrupacionPtr criterio(new PorTematica());

	ItemAgrupablePtr n1(noticia1);
	ItemAgrupablePtr n2(noticia2);
	ASSERT_TRUE(criterio->sonAgrupables(n1, n2));
	ASSERT_TRUE(criterio->sonAgrupables(n2, n1));
}
