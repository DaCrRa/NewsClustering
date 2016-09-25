
#ifndef AGRUPADOR_GRUPOS_H_
#define AGRUPADOR_GRUPOS_H_

#include <list>
#include <assert.h>

#include "CriterioDeAgrupacion.h"

class AgrupadorDeGrupos {
private:
	CriterioDeAgrupacionPtr criterio;

	std::list<std::list<NoticiaIfPtr> >::iterator encontrarGrupo(
			const std::function<bool(NoticiaIfPtr&)>& criterio,
			std::list<std::list<NoticiaIfPtr> >& grupos);
	std::list<NoticiaIfPtr>::iterator encontrarItem(
				const std::function<bool(NoticiaIfPtr&)>& criterio,
				std::list<NoticiaIfPtr>& items);
	std::function<bool(NoticiaIfPtr&)> agrupableCon(NoticiaIfPtr& item);

public:
	AgrupadorDeGrupos(CriterioDeAgrupacionPtr c) : criterio(c) {
		assert(criterio);
	}
	std::list<std::list<NoticiaIfPtr> > agrupar(const std::list<std::list<NoticiaIfPtr> >& grupos);
};

#endif /* AGRUPADOR_GRUPOS_H_ */
