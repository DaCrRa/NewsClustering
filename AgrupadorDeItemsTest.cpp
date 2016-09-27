
#include <gmock/gmock.h>

#include "AgrupadorDeItems.h"
#include "CriterioDeAgrupacionMock.h"
#include "ItemAgrupableMock.h"

using testing::IsEmpty;
using testing::SizeIs;
using testing::ElementsAre;
using testing::Return;
using testing::UnorderedElementsAre;
using testing::Ref;
using testing::Const;
using testing::_;

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithEmptyList_thenReturnsEmptyList) {
   AgrupadorDeItems a(CriterioDeAgrupacionPtr(new CriterioDeAgrupacionMock()));

   ASSERT_THAT(a.agrupar(std::list<ItemAgrupablePtr>()), IsEmpty());
}

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithOneItems_thenReturnsOneGroup) {
   std::shared_ptr<ItemAgrupableMock> noticia(new ItemAgrupableMock());
   EXPECT_CALL(*noticia, esAgrupablePorEntidadMasNombrada(_)).Times(0);

   AgrupadorDeItems a(CriterioDeAgrupacionPtr(new CriterioDeAgrupacionMock()));

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar(std::list<ItemAgrupablePtr>({
	      ItemAgrupablePtr(noticia)
	   }));

   ASSERT_THAT(groups, SizeIs(1));

   ASSERT_THAT(groups.front(), SizeIs(1));
   ASSERT_THAT(groups.front(), ElementsAre(ItemAgrupablePtr(noticia)));
}

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithThreeAgrupableItems_thenReturnsOneGroupWithThreeItems) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(true));

   AgrupadorDeItems a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar(std::list<ItemAgrupablePtr>({
      ItemAgrupablePtr(noticia1),
      ItemAgrupablePtr(noticia2),
      ItemAgrupablePtr(noticia3)
   }));

   ASSERT_THAT(groups, SizeIs(1));

   ASSERT_THAT(groups.front(), SizeIs(3));
   ASSERT_THAT(groups.front(), UnorderedElementsAre(ItemAgrupablePtr(noticia1), ItemAgrupablePtr(noticia2), ItemAgrupablePtr(noticia3)));
}

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithThreeNotAgrupableItems_thenReturnsThreeGroups) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));

   AgrupadorDeItems a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar(std::list<ItemAgrupablePtr>({
         ItemAgrupablePtr(noticia1),
         ItemAgrupablePtr(noticia2),
         ItemAgrupablePtr(noticia3)
   }));

   ASSERT_THAT(groups, SizeIs(3));

   ASSERT_THAT(groups, UnorderedElementsAre( std::list<ItemAgrupablePtr>({ItemAgrupablePtr(noticia1)}),
                                             std::list<ItemAgrupablePtr>({ItemAgrupablePtr(noticia2)}),
                                             std::list<ItemAgrupablePtr>({ItemAgrupablePtr(noticia3)}) ));
}

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithThreeItemsOneAndThreeAreAgrupables_thenReturnsTwoGroups) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   ItemAgrupablePtr n1(noticia1);
   ItemAgrupablePtr n3(noticia3);
   EXPECT_CALL(*criterio, sonAgrupables(n1, n3)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n3, n1)).WillRepeatedly(Return(true));

   AgrupadorDeItems a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar(std::list<ItemAgrupablePtr>({
            ItemAgrupablePtr(noticia1),
            ItemAgrupablePtr(noticia2),
            ItemAgrupablePtr(noticia3)
   }));

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre ( ItemAgrupablePtr(noticia1), ItemAgrupablePtr(noticia3) ),
                                             std::list<ItemAgrupablePtr>({ItemAgrupablePtr(noticia2)})
                                           ));
}

TEST(AgrupadorItemsTest, givenAngrupador_whenCallingAgruparWithThreeItemsOneAndTwoAreAgrupables_thenReturnsTwoGroups) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   ItemAgrupablePtr n1(noticia1);
   ItemAgrupablePtr n2(noticia2);
   EXPECT_CALL(*criterio, sonAgrupables(n1, n2)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n2, n1)).WillRepeatedly(Return(true));

   AgrupadorDeItems a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar(std::list<ItemAgrupablePtr>({
            ItemAgrupablePtr(noticia1),
            ItemAgrupablePtr(noticia2),
            ItemAgrupablePtr(noticia3)
   }));

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre ( ItemAgrupablePtr(noticia1), ItemAgrupablePtr(noticia2) ),
                                             std::list<ItemAgrupablePtr>({ItemAgrupablePtr(noticia3)})
                                           ));
}

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithThreeItemsTwoAndThreeAreAgrupables_thenReturnsTwoGroups) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   ItemAgrupablePtr n3(noticia3);
   ItemAgrupablePtr n2(noticia2);
   EXPECT_CALL(*criterio, sonAgrupables(n2, n3)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n3, n2)).WillRepeatedly(Return(true));

   AgrupadorDeItems a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar(std::list<ItemAgrupablePtr>({
            ItemAgrupablePtr(noticia1),
            ItemAgrupablePtr(noticia2),
            ItemAgrupablePtr(noticia3)
   }));


   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre ( ItemAgrupablePtr(noticia2), ItemAgrupablePtr(noticia3) ),
                                             std::list<ItemAgrupablePtr>({ItemAgrupablePtr(noticia1)})
                                           ));
}

