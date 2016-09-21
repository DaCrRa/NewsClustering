/*
 * Noticia.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "Noticia.h"
#include "list"
#include "EntidadNombrada.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

Noticia::Noticia() {
	this->titulo = "";
	this->cuerpo = "";
	std::list<EntidadNombrada> l;
	this->entidades = l;
	std::list<std::string> p;
	this->entidadesR = p;
}

Noticia::Noticia(std::string titulo, std::string cuerpo, std::string ruta) {
	this->titulo = titulo;
	this->cuerpo = cuerpo;
	this->setPalabrasReservadas(ruta);
	this->setEntidades();
}

void Noticia::setTitulo(std::string titulo) {
	this->titulo = titulo;
}

void Noticia::setCuerpo(std::string cuerpo) {
	this->cuerpo = cuerpo;
}

void Noticia::setPalabrasReservadas(std::string ruta) {
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

void Noticia::actualizar() {
	this->setEntidades();
}

std::string Noticia::getTitulo() const {
	return this->titulo;
}

std::string Noticia::getCuerpo() const {
	return this->cuerpo;
}

EntidadNombrada Noticia::getMasFrecuente() const {
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

std::list<EntidadNombrada> Noticia::getEntidades() const {
	return this->entidades;
}

std::list<std::string> Noticia::getPalabrasReservadas() const {
	return this->entidadesR;
}

std::list<EntidadNombrada> Noticia::getEntidadesRelevantes() const {

	std::string aux = this->cuerpo;
	std::list<EntidadNombrada> lista;
	std::list<EntidadNombrada> misEntidades = this->entidades;

	EntidadNombrada en;
	aux = aux.substr(0, (aux.size() / 3));
	for (std::list<EntidadNombrada>::iterator it = misEntidades.begin();
			it != misEntidades.end(); it++) {
		en = *it;
		if (aux.find(en.getEntidadNombrada()) != std::string::npos) {
			lista.push_back(en);
		}
	}

	return lista;
}

bool Noticia::esAgrupablePorEntidadMasNombrada(NoticiaIf& n) const {
	return getMasFrecuente().esIgual(n.getMasFrecuente());
}

bool Noticia::entidadMasNombradaEstaEnTituloDe(NoticiaIf& n) const {
	EntidadNombrada masFrecuente = getMasFrecuente();
	return masFrecuente.getFrecuencia() > 0 &&
		n.getTitulo().find(masFrecuente.getEntidadNombrada()) != std::string::npos;
}

bool Noticia::entidadesRelevantesAparecenEn(NoticiaIf& n) const {
	std::list<EntidadNombrada> primero = this->getEntidadesRelevantes();
        std::list<EntidadNombrada> segundo = n.getEntidades();
        std::list<EntidadNombrada> final;
        EntidadNombrada en1;
        EntidadNombrada en2;

        for (std::list<EntidadNombrada>::iterator it1 = primero.begin();
                        it1 != primero.end(); it1++) {

                en1 = *it1;
                for (std::list<EntidadNombrada>::iterator it2 = segundo.begin();
                                it2 != segundo.end(); it2++) {

                        en2 = *it2;
                        if (en1.esIgual(en2)) {
                                final.push_back(en2);
                        }
                }
        }

        return final.size() > 0 && final.size() >= (primero.size() / 3.0);
}

bool Noticia::esAgrupablePorTematica(NoticiaIf& n) const {
	return entidadMasNombradaEstaEnTituloDe(n) && entidadesRelevantesAparecenEn(n);
}

std::string Noticia::toString() const {

	std::string salida;
	salida = "TITULO: " + this->titulo + "\n" + "CUERPO: " + this->cuerpo + "\n"
			+ "ENTIDADES: ";

	std::list<EntidadNombrada> lista = this->getEntidades();

	for (std::list<EntidadNombrada>::iterator i = lista.begin();
			i != lista.end(); i++) {
		salida += i->toString();
		salida += " ";
	}

	salida = salida + "\n" + "MAS FRECUENTE: "
			+ this->getMasFrecuente().toString();

	return salida;
}

void Noticia::setEntidades() {
	std::string aux;

	std::istringstream iss(cuerpo);

	while (iss.good()) {
		iss >> aux;
		this->agregarEntidad(aux);
	}
}

void Noticia::agregarEntidad(std::string nombre) {
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

bool Noticia::esletra(char c) const {
	bool salida = false;
	int ascii = static_cast<int>(c);
	if ((ascii >= 65) && (ascii <= 90)) {
		salida = true;
	}
	if ((ascii >= 97) && (ascii <= 122)) {
		salida = true;
	}
	if (ascii < 0) {
		salida = true;
	}
	if ((ascii >= 48) && (ascii <= 57)) {
		salida = true;
	}
	return salida;
}

