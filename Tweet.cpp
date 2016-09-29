/*
 * Tweet.cpp
 *
 *  Created on: 29 de sept. de 2016
 *      Author: dancre
 */

#include "Tweet.h"

EntidadNombrada Tweet::getMasFrecuente() {
	return EntidadNombrada();
}

std::list<EntidadNombrada> Tweet::getEntidades() const {
	return std::list<EntidadNombrada>();
}

bool Tweet::esAgrupablePorEntidadMasNombrada(ItemAgrupable& n) const {
	return false;
}

bool Tweet::esAgrupablePorTematica(ItemAgrupable& n) const {
	return false;
}
