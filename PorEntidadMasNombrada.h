/*
 * PorEntidadMasNombrada.h
 *
 *  Created on: 25 de sept. de 2016
 *      Author: dancre
 */

#ifndef SOURCE_DIRECTORY__PORENTIDADMASNOMBRADA_H_
#define SOURCE_DIRECTORY__PORENTIDADMASNOMBRADA_H_

#include "CriterioDeAgrupacion.h"

class PorEntidadMasNombrada : public CriterioDeAgrupacion {
	bool sonAgrupables(ItemAgrupablePtr& item1, ItemAgrupablePtr& item2);
};


#endif /* SOURCE_DIRECTORY__PORENTIDADMASNOMBRADA_H_ */
