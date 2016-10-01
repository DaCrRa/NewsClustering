/*
 * Tweet.cpp
 *
 *  Created on: 29 de sept. de 2016
 *      Author: dancre
 */

#include "Tweet.h"

#include <algorithm>

int Tweet::getId() const {
	return 0;
}

std::string Tweet::getUsuario() const {
	return "@pepe_perez";
}

std::string Tweet::getTweet() const {
	return tweet;
}

std::string Tweet::getTextoDestacado() const {
	return tweet;
}

bool Tweet::esAgrupablePorTematica(ItemAgrupable& n) const {
	try {
		return !entidades.empty() && ( contieneEntidadMasFrecuenteDe(n) ||
				( n.admiteAgrupacionPorCoincidenciaDeCualquierEntidad() && comparteAlgunaEntidadCon(n) ));
	} catch(NoEntidadNombradaException& e) {
		return false;
	}
}

bool Tweet::contieneEntidadMasFrecuenteDe(ItemAgrupable& n) const {
	return std::find_if(
			entidades.begin(),
			entidades.end(),
			[&](const EntidadNombrada& e) -> bool {
				return e.getEntidadNombrada().compare(n.getMasFrecuente().getEntidadNombrada()) == 0;
			}
	) != entidades.end();
}

bool Tweet::comparteAlgunaEntidadCon(ItemAgrupable& n) const {
	return std::find_if(
			entidades.begin(),
			entidades.end(),
			[&](const EntidadNombrada& e1) -> bool {
				std::list<EntidadNombrada> nEntidades = n.getEntidades();
				return std::find_if(
						nEntidades.begin(),
						nEntidades.end(),
						[&](const EntidadNombrada& e2) -> bool {
							return e1.getEntidadNombrada().compare(e2.getEntidadNombrada()) == 0;
						}) != nEntidades.end();
					}
	) != entidades.end();
}

bool Tweet::admiteAgrupacionPorCoincidenciaDeCualquierEntidad() const {
	return true;
}


