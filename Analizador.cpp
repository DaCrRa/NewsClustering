/*
 * Analizador.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "Analizador.h"
#include "AgrupadorDeGrupos.h"
#include "AgrupadorDeItems.h"
#include "PorTematica.h"
#include "PorEntidadMasNombrada.h"

#include "Noticia.h" // Analizador should not be coupled to Noticia implementation

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string.h>
#include <algorithm>

Analizador::Analizador() {
	std::list<NoticiaIfPtr> l;
	this->noticias = l;
	this->ruta = "";
}

Analizador::Analizador(std::string ruta) {
	this->ruta = ruta;
	this->setNoticias(ruta);
}

std::list<NoticiaIfPtr> Analizador::getNoticias() const {
	std::list<NoticiaIfPtr> l;
	return l;
}

void Analizador::setNoticias(const std::list<NoticiaIfPtr>& noticias) {
	this->noticias = noticias;
}

void Analizador::setNoticias(std::string ruta) {

	std::string rutaRestricciones = ruta + "/ES_stopList.txt";
	std::string rutaNoticias = ruta + "/news";

	int x = 1;
	int y = 1;
	std::string nombreArchivo = "";
	bool mantener = true;
	bool alerta = false;
	std::ifstream f;
	std::string rutaFinal = "";
	std::string colector = "";
	std::string titulo = "";
	std::string cuerpo = "";

	do {
		std::ifstream f;
		nombreArchivo = "/newC" + this->rellenarCeros(x, 5) + "_"
				+ this->rellenarCeros(y, 3) + ".ES.txt";

		rutaFinal = rutaNoticias + nombreArchivo;

		f.open(rutaFinal.c_str(), std::ofstream::in);
		if (f.is_open()) {
			while (!f.eof()) {
				getline(f, colector, '\n');
				if (titulo == "") {
					titulo = titulo + " " + colector;
				} else {
					cuerpo = cuerpo + " " + colector;
				}
			}
			NoticiaIfPtr n(new Noticia(titulo, cuerpo, rutaRestricciones));
			titulo = "";
			cuerpo = "";
			this->noticias.push_front(n);
		}
		y++;

		if (y >= 999) {
			if (!alerta) {
				mantener = false;
			} else {
				x++;
				y = 0;
				alerta = false;
			}
		}
		if (f.is_open()) {
			alerta = true;
		}
		if (x >= 99999) {
			mantener = false;
		}
		f.close();

	} while (mantener);
}

std::list<std::list<NoticiaIfPtr> > Analizador::agruparNoticiasPorEntidadMasFrecuente() {
	AgrupadorDeItems agrupador(CriterioDeAgrupacionPtr(new PorEntidadMasNombrada()));

	return agrupador.agrupar(noticias);
}

std::list<std::list<NoticiaIfPtr> > Analizador::agruparNoticiasPorTematica(const std::list<std::list<NoticiaIfPtr> >& preGrouped) {
	AgrupadorDeGrupos agrupador(CriterioDeAgrupacionPtr(new PorTematica()));
	return agrupador.agrupar(preGrouped);
}

std::string Analizador::rellenarCeros(int n, int size) const {
	std::stringstream ss;
	ss << n;
	std::string aux = ss.str();
	for (int i = aux.size(); i < size; i++) {
		aux = "0" + aux;
	}
	return aux;
}

void Analizador::ordenarNoticias() {

	NoticiaIfPtr aux[this->noticias.size()];
	int c = 0;
	for (std::list<NoticiaIfPtr>::iterator it = this->noticias.begin();
			it != this->noticias.end(); it++) {
		NoticiaIfPtr n = *it;
		aux[c] = n;
		c++;
	}

	int tam = this->noticias.size();
	NoticiaIfPtr temp;
	for (int i = 1; i < tam; i++) {
		for (int j = 0; j < tam - 1; j++) {
			if (aux[j]->getMasFrecuente().getEntidadNombrada()
					> aux[j + 1]->getMasFrecuente().getEntidadNombrada()) {
				temp = aux[j];
				aux[j] = aux[j + 1];
				aux[j + 1] = temp;
			}
		}
	}

	this->noticias.clear();
	for (int i = 0; i < tam; i++) {
		this->noticias.push_back(aux[i]);
	}
}

std::string Analizador::toString() const {
	std::list<NoticiaIfPtr> lista = this->noticias;
	std::string salida = "";
	NoticiaIfPtr aux;
	for (std::list<NoticiaIfPtr>::iterator it = lista.begin(); it != lista.end();
			it++) {
		aux = *it;
		if (salida == "") {
			salida = salida + "Ruta del directorio: " + this->ruta + "\n\n";
		}
		salida = salida + "Titulo: " + aux->getTitulo() + "\n\n";
	}
	return salida;
}

