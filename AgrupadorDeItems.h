/*
 * NoticiaGrouper.h
 *
 *  Created on: 23 de sept. de 2016
 *      Author: dancre
 */

#ifndef SOURCE_DIRECTORY__AGRUPADORDEITEMS_H_
#define SOURCE_DIRECTORY__AGRUPADORDEITEMS_H_

#include "AgrupadorDeGrupos.h"

class AgrupadorDeItems {
private:
	AgrupadorDeGrupos agrupador;
public:
	AgrupadorDeItems(CriterioDeAgrupacionPtr c) : agrupador(c) {}
	std::list<std::list<NoticiaIfPtr> > agrupar(const std::list<NoticiaIfPtr>& items);
};

#endif /* SOURCE_DIRECTORY__AGRUPADORDEITEMS_H_ */
