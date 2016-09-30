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
#include <assert.h>

Noticia::Noticia() : Noticia("", "", "") {}

Noticia::Noticia(const std::string& titulo, const std::string& cuerpo, const std::string& ruta) :
	AbstractItemAgrupable(cuerpo, ruta) {

	assert(UMBRAL_DE_RELEVANCIA_DE_ENTIDADES >= 0
			&& UMBRAL_DE_RELEVANCIA_DE_ENTIDADES <=1);
	assert(UMBRAL_ENTIDADES_RELEVANTES_EN_ITEM_A_AGRUPAR >= 0
			&& UMBRAL_ENTIDADES_RELEVANTES_EN_ITEM_A_AGRUPAR <=1);
	this->titulo = titulo;
	this->cuerpo = cuerpo;
}

void Noticia::setTitulo(std::string titulo) {
	this->titulo = titulo;
}

bool Noticia::admiteAgrupacionPorCoincidenciaDeCualquierEntidad() const {
	return false;
}

void Noticia::setCuerpo(std::string cuerpo) {
	this->cuerpo = cuerpo;
}

std::string Noticia::getTitulo() const {
	return this->titulo;
}

std::string Noticia::getTextoDestacado() const {
	return getTitulo();
}

std::string Noticia::getCuerpo() const {
	return this->cuerpo;
}

std::list<std::string> Noticia::getPalabrasReservadas() const {
	return this->entidadesR;
}

std::list<EntidadNombrada> Noticia::getEntidadesRelevantes() const {

	std::string aux = this->cuerpo;
	std::list<EntidadNombrada> lista;
	std::list<EntidadNombrada> misEntidades = this->entidades;

	EntidadNombrada en;
	aux = aux.substr(0, (aux.size() * UMBRAL_DE_RELEVANCIA_DE_ENTIDADES));
	for (std::list<EntidadNombrada>::iterator it = misEntidades.begin();
			it != misEntidades.end(); it++) {
		en = *it;
		if (aux.find(en.getEntidadNombrada()) != std::string::npos) {
			lista.push_back(en);
		}
	}

	return lista;
}

bool Noticia::entidadMasNombradaEstaEnDestacadoDe(ItemAgrupable& n) const {
	try {
		EntidadNombrada masFrecuente = getMasFrecuente();
		return n.getTextoDestacado().find(masFrecuente.getEntidadNombrada()) != std::string::npos;
	} catch(NoEntidadNombradaException& e) {
		return false;
	}
}

bool Noticia::entidadesRelevantesAparecenEn(ItemAgrupable& n) const {
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

        return final.size() > 0 && final.size() >= (primero.size() * UMBRAL_ENTIDADES_RELEVANTES_EN_ITEM_A_AGRUPAR);
}

bool Noticia::esAgrupablePorTematica(ItemAgrupable& n) const {
	return entidadMasNombradaEstaEnDestacadoDe(n) && entidadesRelevantesAparecenEn(n);
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

