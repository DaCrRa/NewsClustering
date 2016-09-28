/*
 * AbstractItemAgrupable.cpp
 *
 *  Created on: 29 de sept. de 2016
 *      Author: dancre
 */

#include "AbstractItemAgrupable.h"

#include <algorithm>
#include <fstream>
#include <sstream>

AbstractItemAgrupable::AbstractItemAgrupable(const std::string& textoAnalizar, const std::string& ruta) {
	setPalabrasReservadas(ruta);
	setEntidades(textoAnalizar);
}

std::list<EntidadNombrada> AbstractItemAgrupable::getEntidades() const {
	return this->entidades;
}

EntidadNombrada AbstractItemAgrupable::getMasFrecuente() const {
	auto entidadNombradaMax = std::max_element(
		entidades.begin(),
		entidades.end(),
		[&](const EntidadNombrada& e1, const EntidadNombrada& e2) -> bool {
			return e1.getFrecuencia() < e2.getFrecuencia();
		}
	);
	if (entidadNombradaMax == entidades.end()) {
		throw NoEntidadNombradaException();
	}
	return *entidadNombradaMax;
}

void AbstractItemAgrupable::setPalabrasReservadas(const std::string& ruta) {
	std::ifstream f;
	f.open(ruta.c_str(), std::ofstream::in);
	while (f.good()) {
		std::string aux;
		f >> aux;
		if (aux.compare("") != 0) {
			this->entidadesR.push_back(aux);
		}
	}
}

void AbstractItemAgrupable::setEntidades(const std::string& textoAnalizar) {
	std::string aux;

	std::istringstream iss(textoAnalizar);

	while (iss.good()) {
		iss >> aux;
		this->agregarEntidad(aux);
	}
}

void AbstractItemAgrupable::agregarEntidad(const std::string& nombre) {
	bool empezar = true;
	for (std::list<std::string>::iterator i = this->entidadesR.begin();
			i != this->entidadesR.end(); i++) {

		if (i->compare(nombre) == 0) {
			empezar = false;
			break;
		}
	}
	if (empezar) {
		bool add = true;
		for (std::list<EntidadNombrada>::iterator it = this->entidades.begin();
				it != this->entidades.end(); it++) {
			if (it->getEntidadNombrada().compare(nombre) == 0) {
				it->setFrecuencia(it->getFrecuencia() + 1);
				add = false;
			}
		}
		if (add) {
			int aux = static_cast<int>(nombre[0]);
			if ((aux >= 65) && (aux <= 90)) {
				EntidadNombrada aux(nombre, 1);
				this->entidades.push_back(aux);
			}
		}
	}
}
