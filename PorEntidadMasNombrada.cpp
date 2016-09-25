/*
 * PorTematica.cpp
 *
 *  Created on: 25 de sept. de 2016
 *      Author: dancre
 */

#include "PorEntidadMasNombrada.h"

bool PorEntidadMasNombrada::sonAgrupables(NoticiaIfPtr& item1, NoticiaIfPtr& item2) {
	return item1->esAgrupablePorEntidadMasNombrada(*item2) ||
			item2->esAgrupablePorEntidadMasNombrada(*item1);
}
