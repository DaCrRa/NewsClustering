
#include <gmock/gmock.h>

#include "AgrupadorDeItems.h"
#include "NoticiaIfMock.h"
#include "CriterioDeAgrupacionMock.h"

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

   ASSERT_THAT(a.agrupar(std::list<NoticiaIfPtr>()), IsEmpty());
}

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithOneNoticias_thenReturnsOneGroupWithOneNoticias) {
   std::shared_ptr<NoticiaIfMock> noticia(new NoticiaIfMock());
   EXPECT_CALL(*noticia, esAgrupablePorEntidadMasNombrada(_)).Times(0);

   AgrupadorDeItems a(CriterioDeAgrupacionPtr(new CriterioDeAgrupacionMock()));

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar(std::list<NoticiaIfPtr>({
	      NoticiaIfPtr(noticia)
	   }));

   ASSERT_THAT(groups, SizeIs(1));

   ASSERT_THAT(groups.front(), SizeIs(1));
   ASSERT_THAT(groups.front(), ElementsAre(NoticiaIfPtr(noticia)));
}

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithThreeAgrupableNoticias_thenReturnsOneGroupWithThreeNoticias) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(true));

   AgrupadorDeItems a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar(std::list<NoticiaIfPtr>({
      NoticiaIfPtr(noticia1),
      NoticiaIfPtr(noticia2),
      NoticiaIfPtr(noticia3)
   }));

   ASSERT_THAT(groups, SizeIs(1));

   ASSERT_THAT(groups.front(), SizeIs(3));
   ASSERT_THAT(groups.front(), UnorderedElementsAre(NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2), NoticiaIfPtr(noticia3)));
}

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithThreeNotAgrupableNoticias_thenReturnsThreeGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));

   AgrupadorDeItems a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar(std::list<NoticiaIfPtr>({
         NoticiaIfPtr(noticia1),
         NoticiaIfPtr(noticia2),
         NoticiaIfPtr(noticia3)
   }));

   ASSERT_THAT(groups, SizeIs(3));

   ASSERT_THAT(groups, UnorderedElementsAre( std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia1)}),
                                             std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia2)}),
                                             std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia3)}) ));
}

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithThreeNoticiasOneAndThreeAreAgrupables_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   NoticiaIfPtr n1(noticia1);
   NoticiaIfPtr n3(noticia3);
   EXPECT_CALL(*criterio, sonAgrupables(n1, n3)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n3, n1)).WillRepeatedly(Return(true));

   AgrupadorDeItems a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar(std::list<NoticiaIfPtr>({
            NoticiaIfPtr(noticia1),
            NoticiaIfPtr(noticia2),
            NoticiaIfPtr(noticia3)
   }));

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre ( NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia3) ),
                                             std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia2)})
                                           ));
}

TEST(AgrupadorItemsTest, givenAngrupador_whenCallingAgruparWithThreeNoticiasOneAndTwoAreAgrupables_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   NoticiaIfPtr n1(noticia1);
   NoticiaIfPtr n2(noticia2);
   EXPECT_CALL(*criterio, sonAgrupables(n1, n2)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n2, n1)).WillRepeatedly(Return(true));

   AgrupadorDeItems a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar(std::list<NoticiaIfPtr>({
            NoticiaIfPtr(noticia1),
            NoticiaIfPtr(noticia2),
            NoticiaIfPtr(noticia3)
   }));

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre ( NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2) ),
                                             std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia3)})
                                           ));
}

TEST(AgrupadorItemsTest, givenAgrupador_whenCallingAgruparWithThreeNoticiasTwoAndThreeAreAgrupables_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<CriterioDeAgrupacionMock> criterio(new CriterioDeAgrupacionMock());
   EXPECT_CALL(*criterio, sonAgrupables(_, _)).WillRepeatedly(Return(false));
   NoticiaIfPtr n3(noticia3);
   NoticiaIfPtr n2(noticia2);
   EXPECT_CALL(*criterio, sonAgrupables(n2, n3)).WillRepeatedly(Return(true));
   EXPECT_CALL(*criterio, sonAgrupables(n3, n2)).WillRepeatedly(Return(true));

   AgrupadorDeItems a(criterio);

   std::list<std::list<NoticiaIfPtr> > groups = a.agrupar(std::list<NoticiaIfPtr>({
            NoticiaIfPtr(noticia1),
            NoticiaIfPtr(noticia2),
            NoticiaIfPtr(noticia3)
   }));


   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre ( NoticiaIfPtr(noticia2), NoticiaIfPtr(noticia3) ),
                                             std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia1)})
                                           ));
}

