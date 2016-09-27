/*
 * PorTematica.cpp
 *
 *  Created on: 25 de sept. de 2016
 *      Author: dancre
 */

#include "PorTematica.h"

bool PorTematica::sonAgrupables(ItemAgrupablePtr& item1, ItemAgrupablePtr& item2) {
	return item1->esAgrupablePorTematica(*item2) ||
			item2->esAgrupablePorTematica(*item1);
}
