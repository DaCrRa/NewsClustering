/*
 * NoticiaGrouper.cpp
 *
 *  Created on: 23 de sept. de 2016
 *      Author: dancre
 */

#include "AgrupadorDeItems.h"

std::list<std::list<NoticiaIfPtr> > AgrupadorDeItems::agrupar(const std::list<NoticiaIfPtr>& items) {
	std::list<std::list<NoticiaIfPtr> > itemsEnGruposDeUno;
	for (NoticiaIfPtr item : items) {
		itemsEnGruposDeUno.push_back(std::list<NoticiaIfPtr>({item}));
	}
	return agrupador.agrupar(itemsEnGruposDeUno);
}
