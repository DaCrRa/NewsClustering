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
	try {
		EntidadNombrada masFrecuente = n.getMasFrecuente();
		std::list<EntidadNombrada> nEntidades = n.getEntidades();
		return std::find_if(entidades.begin(),
				entidades.end(),
				[&](const EntidadNombrada& e) -> bool {
					return e.getEntidadNombrada().compare(masFrecuente.getEntidadNombrada()) == 0;
				}
		) != entidades.end() || std::find_if(entidades.begin(),
				entidades.end(),
				[&](const EntidadNombrada& e1) -> bool {
					return std::find_if(nEntidades.begin(), nEntidades.end(), [&](const EntidadNombrada& e2) -> bool {
						return e1.getEntidadNombrada().compare(e2.getEntidadNombrada()) == 0;
					}) != nEntidades.end();
				}
		) != entidades.end();
	} catch(NoEntidadNombradaException& e) {
		return false;
	}
}
