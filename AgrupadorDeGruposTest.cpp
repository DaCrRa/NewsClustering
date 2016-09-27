
#include <gmock/gmock.h>

#include "AgrupadorDeGrupos.h"
#include "ItemAgrupableMock.h"
#include "CriterioDeAgrupacionMock.h"

using testing::IsEmpty;
using testing::SizeIs;
using testing::ElementsAre;
using testing::Return;
using testing::UnorderedElementsAre;
using testing::Ref;
using testing::_;

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithNoGroupings_thenReturnsEmptyGroup) {
   AgrupadorDeGrupos a(CriterioDeAgrupacionPtr(new CriterioDeAgrupacionMock()));

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar({});

   ASSERT_THAT(groups, IsEmpty());
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithOneEmptyGrouping_thenReturnsEmptyGroup) {
   AgrupadorDeGrupos a(CriterioDeAgrupacionPtr(new CriterioDeAgrupacionMock()));

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar({std::list<ItemAgrupablePtr>({})});

   ASSERT_THAT(groups, IsEmpty());
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithOneGroupingWithOneItem_thenReturnsOneGroup) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());

   AgrupadorDeGrupos a(CriterioDeAgrupacionPtr(new CriterioDeAgrupacionMock()));

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar({std::list<ItemAgrupablePtr>({ItemAgrupablePtr(noticia1)})});

   ASSERT_THAT(groups, UnorderedElementsAre(std::list<ItemAgrupablePtr>({ItemAgrupablePtr(noticia1)})));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithThreeGroupsOfItemsNotGroupable_thenReturnsThreeGroups) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia4(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia5(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia6(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));

   AgrupadorDeGrupos a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar({
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia1), ItemAgrupablePtr(noticia2)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia3), ItemAgrupablePtr(noticia4)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia5), ItemAgrupablePtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre(
      UnorderedElementsAre(ItemAgrupablePtr(noticia1), ItemAgrupablePtr(noticia2)),
      UnorderedElementsAre(ItemAgrupablePtr(noticia3), ItemAgrupablePtr(noticia4)),
      UnorderedElementsAre(ItemAgrupablePtr(noticia5), ItemAgrupablePtr(noticia6))
   ));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparThreeGroupsOfItemsAllGroupable_thenReturnsOneGroup) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia4(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia5(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia6(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(true));

   AgrupadorDeGrupos a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar({
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia1), ItemAgrupablePtr(noticia2)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia3), ItemAgrupablePtr(noticia4)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia5), ItemAgrupablePtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre (
      ItemAgrupablePtr(noticia1),
      ItemAgrupablePtr(noticia2),
      ItemAgrupablePtr(noticia3),
      ItemAgrupablePtr(noticia4),
      ItemAgrupablePtr(noticia5),
      ItemAgrupablePtr(noticia6)
   )));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithThreeGroupsOfItemsOneAndTwoGroupable_thenReturnsTwoGroups) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia4(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia5(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia6(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   ItemAgrupablePtr n2(noticia2);
   ItemAgrupablePtr n3(noticia3);
   EXPECT_CALL(*criterio, sonAgrupables(n2, n3)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n3, n2)).WillRepeatedly(Return(true));

   AgrupadorDeGrupos a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar({
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia1), ItemAgrupablePtr(noticia2)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia3), ItemAgrupablePtr(noticia4)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia5), ItemAgrupablePtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre(
      UnorderedElementsAre (
         ItemAgrupablePtr(noticia1),
         ItemAgrupablePtr(noticia2),
         ItemAgrupablePtr(noticia3),
         ItemAgrupablePtr(noticia4)),
      UnorderedElementsAre (
         ItemAgrupablePtr(noticia5),
         ItemAgrupablePtr(noticia6))
   ));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithThreeGroupsOfItemsOneAndThreeGroupable_thenReturnsTwoGroups) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia4(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia5(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia6(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   ItemAgrupablePtr n2(noticia2);
   ItemAgrupablePtr n5(noticia5);
   EXPECT_CALL(*criterio, sonAgrupables(n2, n5)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n5, n2)).WillRepeatedly(Return(true));

   AgrupadorDeGrupos a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar({
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia1), ItemAgrupablePtr(noticia2)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia3), ItemAgrupablePtr(noticia4)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia5), ItemAgrupablePtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre(
      UnorderedElementsAre (
         ItemAgrupablePtr(noticia1),
         ItemAgrupablePtr(noticia2),
         ItemAgrupablePtr(noticia5),
         ItemAgrupablePtr(noticia6)),
      UnorderedElementsAre (
         ItemAgrupablePtr(noticia4),
         ItemAgrupablePtr(noticia3))
   ));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparThreeGroupsOfItemsTwoAndThreeGroupable_thenReturnsTwoGroups) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia4(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia5(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia6(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   ItemAgrupablePtr n5(noticia5);
   ItemAgrupablePtr n3(noticia3);
   EXPECT_CALL(*criterio, sonAgrupables(n5, n3)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n3, n5)).WillRepeatedly(Return(true));

   AgrupadorDeGrupos a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar({
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia1), ItemAgrupablePtr(noticia2)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia3), ItemAgrupablePtr(noticia4)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia5), ItemAgrupablePtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre(
      UnorderedElementsAre (
         ItemAgrupablePtr(noticia3),
         ItemAgrupablePtr(noticia4),
         ItemAgrupablePtr(noticia5),
         ItemAgrupablePtr(noticia6)),
      UnorderedElementsAre (
         ItemAgrupablePtr(noticia1),
         ItemAgrupablePtr(noticia2))
   ));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithThreeGroupsOneGroupsWithTwoAndTwoWithThree_thenReturnsOneGroup) {
   std::shared_ptr<ItemAgrupableMock> noticia1(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia2(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia3(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia4(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia5(new ItemAgrupableMock());
   std::shared_ptr<ItemAgrupableMock> noticia6(new ItemAgrupableMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   ItemAgrupablePtr n1(noticia1);
   ItemAgrupablePtr n4(noticia4);
   EXPECT_CALL(*criterio, sonAgrupables(n1, n4)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n4, n1)).WillRepeatedly(Return(true));
   ItemAgrupablePtr n5(noticia5);
   ItemAgrupablePtr n3(noticia3);
   EXPECT_CALL(*criterio, sonAgrupables(n5, n3)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n3, n5)).WillRepeatedly(Return(true));


   AgrupadorDeGrupos a(criterio);

   std::list<std::list<ItemAgrupablePtr> > groups = a.agrupar({
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia1), ItemAgrupablePtr(noticia2)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia3), ItemAgrupablePtr(noticia4)} ),
	      std::list<ItemAgrupablePtr>( {ItemAgrupablePtr(noticia5), ItemAgrupablePtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre (
      ItemAgrupablePtr(noticia1),
      ItemAgrupablePtr(noticia2),
      ItemAgrupablePtr(noticia3),
      ItemAgrupablePtr(noticia4),
      ItemAgrupablePtr(noticia5),
      ItemAgrupablePtr(noticia6)
   )));
}

