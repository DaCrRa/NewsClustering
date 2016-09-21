
#include <gmock/gmock.h>

#include "Analizador.h"
#include "NoticiaIfMock.h"

using testing::IsEmpty;
using testing::SizeIs;
using testing::ElementsAre;
using testing::Return;
using testing::UnorderedElementsAre;
using testing::Ref;
using testing::_;

TEST(AnalizadorTest, givenAnalizadorWithEmptyNoticias_whenCallingAgrupar_thenReturnsEmptyList) {
   Analizador a;

   ASSERT_THAT(a.agruparNoticiasPorEntidadMasFrecuente(), IsEmpty());
}

TEST(AnalizadorTest, givenAnalizadorWithOneNoticias_whenCallingAgrupar_thenReturnsOneGroupWithOneNoticias) {
   std::shared_ptr<NoticiaIfMock> noticia(new NoticiaIfMock());
   EXPECT_CALL(*noticia, esAgrupablePorEntidadMasNombrada(_)).Times(0);

   Analizador a;

   a.setNoticias(std::list<NoticiaIfPtr>({
      NoticiaIfPtr(noticia)
   }));

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorEntidadMasFrecuente();

   ASSERT_THAT(groups, SizeIs(1));

   ASSERT_THAT(groups.front(), SizeIs(1));
   ASSERT_THAT(groups.front(), ElementsAre(NoticiaIfPtr(noticia)));
}

TEST(AnalizadorTest, givenAnalizadorWithThreeAgrupableNoticias_whenCallingAgrupar_thenReturnsOneGroupWithThreeNoticias) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(Ref(*noticia2))).Times(1).WillOnce(Return(true));
   EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(Ref(*noticia3))).Times(1).WillOnce(Return(true));
   EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).Times(0);
   EXPECT_CALL(*noticia3, esAgrupablePorEntidadMasNombrada(_)).Times(0);

   Analizador a;

   a.setNoticias(std::list<NoticiaIfPtr>({
      NoticiaIfPtr(noticia1),
      NoticiaIfPtr(noticia2),
      NoticiaIfPtr(noticia3)
   }));

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorEntidadMasFrecuente();

   ASSERT_THAT(groups, SizeIs(1));

   ASSERT_THAT(groups.front(), SizeIs(3));
   ASSERT_THAT(groups.front(), UnorderedElementsAre(NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2), NoticiaIfPtr(noticia3)));
}

TEST(AnalizadorTest, givenAnalizadorWithThreeNotAgrupableNoticias_whenCallingAgrupar_thenReturnsThreeGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));

   Analizador a;

   a.setNoticias(std::list<NoticiaIfPtr>({
      NoticiaIfPtr(noticia1),
      NoticiaIfPtr(noticia2),
      NoticiaIfPtr(noticia3)
   }));

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorEntidadMasFrecuente();

   ASSERT_THAT(groups, SizeIs(3));

   ASSERT_THAT(groups, UnorderedElementsAre( std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia1)}),
                                             std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia2)}),
                                             std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia3)}) ));
}

TEST(AnalizadorTest, givenAnalizadorWithThreeNoticiasOneAndThreeAreAgrupables_whenCallingAgrupar_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorEntidadMasNombrada(Ref(*noticia1))).Times(1).WillOnce(Return(true));

   Analizador a;

   a.setNoticias(std::list<NoticiaIfPtr>({
      NoticiaIfPtr(noticia1),
      NoticiaIfPtr(noticia2),
      NoticiaIfPtr(noticia3)
   }));

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorEntidadMasFrecuente();

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre ( NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia3) ),
                                             std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia2)})
                                           ));
}

TEST(AnalizadorTest, givenAnalizadorWithThreeNoticiasOneAndTwoAreAgrupables_whenCallingAgrupar_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(Ref(*noticia2))).Times(1).WillOnce(Return(true));

   Analizador a;

   a.setNoticias(std::list<NoticiaIfPtr>({
      NoticiaIfPtr(noticia1),
      NoticiaIfPtr(noticia2),
      NoticiaIfPtr(noticia3)
   }));

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorEntidadMasFrecuente();

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre ( NoticiaIfPtr(noticia1), NoticiaIfPtr(noticia2) ),
                                             std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia3)})
                                           ));
}

TEST(AnalizadorTest, givenAnalizadorWithThreeNoticiasTwoAndThreeAreAgrupables_whenCallingAgrupar_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorEntidadMasNombrada(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorEntidadMasNombrada(Ref(*noticia2))).Times(1).WillOnce(Return(true));

   Analizador a;

   a.setNoticias(std::list<NoticiaIfPtr>({
      NoticiaIfPtr(noticia1),
      NoticiaIfPtr(noticia2),
      NoticiaIfPtr(noticia3)
   }));

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorEntidadMasFrecuente();

   ASSERT_THAT(groups, UnorderedElementsAre( UnorderedElementsAre ( NoticiaIfPtr(noticia2), NoticiaIfPtr(noticia3) ),
                                             std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia1)})
                                           ));
}

TEST(AnalizadorTest, givenEmptyGrouping_whenCallingAgrupar_thenReturnsEmptyGroup) {
   Analizador a;

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorTematica({});

   ASSERT_THAT(groups, IsEmpty());
}

TEST(AnalizadorTest, givenOneGroupingWithOneNoticia_whenCallingAgrupar_thenReturnsOneGroup) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());

   Analizador a;

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorTematica(
      {std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia1)})}
   );

   ASSERT_THAT(groups, UnorderedElementsAre(std::list<NoticiaIfPtr>({NoticiaIfPtr(noticia1)})));
}

TEST(AnalizadorTest, givenThreeGroupsOfNoticiasNotGroupable_whenCallingAgrupar_thenReturnsThreeGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia4, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia5, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia6, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));

   Analizador a;

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorTematica({
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

TEST(AnalizadorTest, givenThreeGroupsOfNoticiasAllGroupable_whenCallingAgrupar_thenReturnsOneGroup) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia4, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia5, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia6, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia1, esAgrupablePorTematica(Ref(*noticia3))).Times(1).WillOnce(Return(true));
   EXPECT_CALL(*noticia2, esAgrupablePorTematica(Ref(*noticia6))).Times(1).WillOnce(Return(true));

   Analizador a;

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorTematica({
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

TEST(AnalizadorTest, givenThreeGroupsOfNoficiasOneAndTwoGroupable_whenCallingAgrupar_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia4, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia5, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia6, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorTematica(Ref(*noticia3))).Times(1).WillOnce(Return(true));

   Analizador a;

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorTematica({
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

TEST(AnalizadorTest, givenThreeGroupsOfNoticiasOneAndThreeGroupable_whenCallingAgrupar_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia4, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia5, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia6, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorTematica(Ref(*noticia5))).Times(1).WillOnce(Return(true));

   Analizador a;

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorTematica({
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

TEST(AnalizadorTest, givenThreeGroupsOfNoticiasTwoAndThreeGroupable_whenCallingAgrupar_thenReturnsTwoGroups) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia4, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia5, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia6, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia5, esAgrupablePorTematica(Ref(*noticia3))).Times(1).WillOnce(Return(true));

   Analizador a;

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorTematica({
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

TEST(AnalizadorTest, givenAnalizadorWithThreeGroupsOneGroupsWithTwoAndTwoWithThree_whenCallingAgrupar_thenReturnsOneGroup) {
   std::shared_ptr<NoticiaIfMock> noticia1(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia2(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia3(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia4(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia5(new NoticiaIfMock());
   std::shared_ptr<NoticiaIfMock> noticia6(new NoticiaIfMock());
   EXPECT_CALL(*noticia1, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia2, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia3, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia4, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia5, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia6, esAgrupablePorTematica(_)).WillRepeatedly(Return(false));
   EXPECT_CALL(*noticia1, esAgrupablePorTematica(Ref(*noticia4))).Times(1).WillOnce(Return(true));
   EXPECT_CALL(*noticia6, esAgrupablePorTematica(Ref(*noticia3))).Times(1).WillOnce(Return(true));

   Analizador a;

   std::list<std::list<NoticiaIfPtr> > groups = a.agruparNoticiasPorTematica({
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
