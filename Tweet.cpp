/*
 * Tweet.cpp
 *
 *  Created on: 29 de sept. de 2016
 *      Author: dancre
 */

#include "Tweet.h"

#include <algorithm>

std::string Tweet::getTextoDestacado() const {
	return "";
}

bool Tweet::esAgrupablePorTematica(ItemAgrupable& n) const {
	EntidadNombrada masFrecuente = n.getMasFrecuente();
	return std::find_if(entidades.begin(),
			entidades.end(),
			[&](const EntidadNombrada& e) -> bool {
				return e.getEntidadNombrada().compare(masFrecuente.getEntidadNombrada()) == 0;
			}
	) != entidades.end();
}
