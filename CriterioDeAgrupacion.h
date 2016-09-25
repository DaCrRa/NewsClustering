/*
 * CriterioDeAgrupacion.h
 *
 *  Created on: 25 de sept. de 2016
 *      Author: dancre
 */

#ifndef SOURCE_DIRECTORY__CRITERIODEAGRUPACION_H_
#define SOURCE_DIRECTORY__CRITERIODEAGRUPACION_H_

#include "NoticiaIf.h"

#include <memory>

class CriterioDeAgrupacion;
typedef std::shared_ptr<CriterioDeAgrupacion> CriterioDeAgrupacionPtr;

class CriterioDeAgrupacion {
public:
	virtual bool sonAgrupables(NoticiaIfPtr& item1, NoticiaIfPtr& item2) = 0;
	virtual ~CriterioDeAgrupacion() {};
};

#endif /* SOURCE_DIRECTORY__CRITERIODEAGRUPACION_H_ */
