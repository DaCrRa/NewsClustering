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
