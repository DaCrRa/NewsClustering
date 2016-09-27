/*
 * NoticiaGrouper.cpp
 *
 *  Created on: 23 de sept. de 2016
 *      Author: dancre
 */

#include "AgrupadorDeItems.h"

std::list<std::list<ItemAgrupablePtr> > AgrupadorDeItems::agrupar(const std::list<ItemAgrupablePtr>& items) {
	std::list<std::list<ItemAgrupablePtr> > itemsEnGruposDeUno;
	for (ItemAgrupablePtr item : items) {
		itemsEnGruposDeUno.push_back(std::list<ItemAgrupablePtr>({item}));
	}
	return agrupador.agrupar(itemsEnGruposDeUno);
}
