
#include <gmock/gmock.h>

#include "AgrupadorDeGrupos.h"
#include "NoticiaIfMock.h"
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

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar({});

   ASSERT_THAT(groups, IsEmpty());
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithOneEmptyGrouping_thenReturnsEmptyGroup) {
   AgrupadorDeGrupos a(CriterioDeAgrupacionPtr(new CriterioDeAgrupacionMock()));

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar({std::list<NoticiaIfPtr>({})});

   ASSERT_THAT(groups, IsEmpty());
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithOneGroupingWithOneNoticia_thenReturnsOneGroup) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());

   AgrupadorDeGrupos a(CriterioDeAgrupacionPtr(new CriterioDeAgrupacionMock()));

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar({std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia1)})});

   ASSERT_THAT(groups, UnorderedElementsAre(std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia1)})));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithThreeGroupsOfNoticiasNotGroupable_thenReturnsThreeGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));

   AgrupadorDeGrupos a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar({
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia3), NoticiaIfPtr(noticia4)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia5), NoticiaIfPtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre(
      UnorderedElementsAre(NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2)),
      UnorderedElementsAre(NoticiaIfPtr(noticia3), NoticiaIfPtr(noticia4)),
      UnorderedElementsAre(NoticiaIfPtr(noticia5), NoticiaIfPtr(noticia6))
   ));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparThreeGroupsOfNoticiasAllGroupable_thenReturnsOneGroup) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(true));

   AgrupadorDeGrupos a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar({
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia3), NoticiaIfPtr(noticia4)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia5), NoticiaIfPtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre (
      NoticiaIfPtr(noticia1),
      NoticiaIfPtr(noticia2),
      NoticiaIfPtr(noticia3),
      NoticiaIfPtr(noticia4),
      NoticiaIfPtr(noticia5),
      NoticiaIfPtr(noticia6)
   )));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithThreeGroupsOfNoficiasOneAndTwoGroupable_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   NoticiaIfPtr n2(noticia2);
   NoticiaIfPtr n3(noticia3);
   EXPECT_CALL(*criterio, sonAgrupables(n2, n3)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n3, n2)).WillRepeatedly(Return(true));

   AgrupadorDeGrupos a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar({
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia3), NoticiaIfPtr(noticia4)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia5), NoticiaIfPtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre(
      UnorderedElementsAre (
         NoticiaIfPtr(noticia1),
         NoticiaIfPtr(noticia2),
         NoticiaIfPtr(noticia3),
         NoticiaIfPtr(noticia4)),
      UnorderedElementsAre (
         NoticiaIfPtr(noticia5),
         NoticiaIfPtr(noticia6))
   ));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithThreeGroupsOfNoticiasOneAndThreeGroupable_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   NoticiaIfPtr n2(noticia2);
   NoticiaIfPtr n5(noticia5);
   EXPECT_CALL(*criterio, sonAgrupables(n2, n5)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n5, n2)).WillRepeatedly(Return(true));

   AgrupadorDeGrupos a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar({
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia3), NoticiaIfPtr(noticia4)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia5), NoticiaIfPtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre(
      UnorderedElementsAre (
         NoticiaIfPtr(noticia1),
         NoticiaIfPtr(noticia2),
         NoticiaIfPtr(noticia5),
         NoticiaIfPtr(noticia6)),
      UnorderedElementsAre (
         NoticiaIfPtr(noticia4),
         NoticiaIfPtr(noticia3))
   ));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparThreeGroupsOfNoticiasTwoAndThreeGroupable_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   NoticiaIfPtr n5(noticia5);
   NoticiaIfPtr n3(noticia3);
   EXPECT_CALL(*criterio, sonAgrupables(n5, n3)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n3, n5)).WillRepeatedly(Return(true));

   AgrupadorDeGrupos a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar({
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia3), NoticiaIfPtr(noticia4)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia5), NoticiaIfPtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre(
      UnorderedElementsAre (
         NoticiaIfPtr(noticia3),
         NoticiaIfPtr(noticia4),
         NoticiaIfPtr(noticia5),
         NoticiaIfPtr(noticia6)),
      UnorderedElementsAre (
         NoticiaIfPtr(noticia1),
         NoticiaIfPtr(noticia2))
   ));
}

TEST(AgrupadorGruposTest, givenAgrupador_whenCallingAgruparWithThreeGroupsOneGroupsWithTwoAndTwoWithThree_thenReturnsOneGroup) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   NoticiaIfPtr n1(noticia1);
   NoticiaIfPtr n4(noticia4);
   EXPECT_CALL(*criterio, sonAgrupables(n1, n4)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n4, n1)).WillRepeatedly(Return(true));
   NoticiaIfPtr n5(noticia5);
   NoticiaIfPtr n3(noticia3);
   EXPECT_CALL(*criterio, sonAgrupables(n5, n3)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n3, n5)).WillRepeatedly(Return(true));


   AgrupadorDeGrupos a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar({
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia3), NoticiaIfPtr(noticia4)} ),
	      std::list<NoticiaIfPtr>( {NoticiaIfPtr(noticia5), NoticiaIfPtr(noticia6)} )
	   });

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre (
      NoticiaIfPtr(noticia1),
      NoticiaIfPtr(noticia2),
      NoticiaIfPtr(noticia3),
      NoticiaIfPtr(noticia4),
      NoticiaIfPtr(noticia5),
      NoticiaIfPtr(noticia6)
   )));
}

