/*
 * CriterioDeAgrupacion.h
 *
 *  Created on: 25 de sept. de 2016
 *      Author: dancre
 */

#ifndef SOURCE_DIRECTORY__CRITERIODEAGRUPACION_H_
#define SOURCE_DIRECTORY__CRITERIODEAGRUPACION_H_

#include <memory>
#include "ItemAgrupable.h"

class CriterioDeAgrupacion;
typedef std::shared_ptr<CriterioDeAgrupacion> CriterioDeAgrupacionPtr;

class CriterioDeAgrupacion {
public:
	virtual bool sonAgrupables(ItemAgrupablePtr& item1, ItemAgrupablePtr& item2) = 0;
	virtual ~CriterioDeAgrupacion() {};
};

#endif /* SOURCE_DIRECTORY__CRITERIODEAGRUPACION_H_ */
