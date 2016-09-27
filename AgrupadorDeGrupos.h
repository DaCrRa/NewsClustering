
#ifndef AGRUPADOR_GRUPOS_H_
#define AGRUPADOR_GRUPOS_H_

#include <list>
#include <assert.h>

#include "CriterioDeAgrupacion.h"

class AgrupadorDeGrupos {
private:
	CriterioDeAgrupacionPtr criterio;

	std::list<std::list<ItemAgrupablePtr> >::iterator encontrarGrupo(
			const std::function<bool(ItemAgrupablePtr&)>& criterio,
			std::list<std::list<ItemAgrupablePtr> >& grupos);
	std::list<ItemAgrupablePtr>::iterator encontrarItem(
				const std::function<bool(ItemAgrupablePtr&)>& criterio,
				std::list<ItemAgrupablePtr>& items);
	std::function<bool(ItemAgrupablePtr&)> agrupableCon(ItemAgrupablePtr& item);

public:
	AgrupadorDeGrupos(CriterioDeAgrupacionPtr c) : criterio(c) {
		assert(criterio);
	}
	std::list<std::list<ItemAgrupablePtr> > agrupar(const std::list<std::list<ItemAgrupablePtr> >& grupos);
};

#endif /* AGRUPADOR_GRUPOS_H_ */
