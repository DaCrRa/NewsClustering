/*
 * Analizador.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "Analizador.h"

#include "Noticia.h" // Analizador should not be coupled to Noticia implementation

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string.h>

Analizador::Analizador() {
	std::list<NoticiaIfPtr> l;
	this->noticias = l;
	this->ruta = "";
}

Analizador::Analizador(std::string ruta) {
	this->ruta = ruta;
	this->setNoticas(ruta);
}

std::list<NoticiaIfPtr> Analizador::getNoticias() const {
	std::list<NoticiaIfPtr> l;
	return l;
}

void Analizador::setNoticas(std::string ruta) {

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

	this->ordenarNoticias();

        std::list<std::list<NoticiaIfPtr> > groups;

	std::list<NoticiaIfPtr> lista = this->noticias;
	std::string salida = "";
	std::string entidad = "";

	while (!lista.empty()) {
		std::list<NoticiaIfPtr> grupo;
		NoticiaIfPtr noticiaDeReferencia(lista.front());
		lista.pop_front();
		grupo.push_back(noticiaDeReferencia);
		for (std::list<NoticiaIfPtr>::iterator it = lista.begin(); it != lista.end(); ) {
			NoticiaIfPtr noticiaComparada(*it);
			if (noticiaDeReferencia->esAgrupablePorEntidadMasNombrada(*noticiaComparada)) {
				grupo.push_back(noticiaComparada);
				it = lista.erase(it);
			}
			if (it != lista.end()) {
				++it;
			}
		}
		groups.push_back(grupo);
	}

	return groups;
}
/*
std::string Analizador::agruparNoticiasGeneral() {

	std::cout << "*";

	std::list<EntidadNombrada> agrupacion[this->noticias.size()];

	this->ordenarNoticias();

	std::list<NoticiaIfPtr> ln1 = this->noticias;
	std::list<NoticiaIfPtr> ln2 = this->noticias;

	std::string salida = "";
	std::string agrupaciones = "";
	Noticia n2;
	EntidadNombrada en;
	EntidadNombrada en2;

	unsigned int c = 0;
	for (std::list<NoticiaIfPtr>::iterator it1 = ln1.begin(); it1 != ln1.end();
			it1++) {

		bool sola = true;
		NoticiaIfPtr n = *it1;
		for (std::list<NoticiaIfPtr>::iterator it2 = ln1.begin(); it2 != ln1.end();
				it2++) {
			NoticiaIfPtr n2 = *it2;

			if ((distance(it1, it2) != 0)) {
				if ((n->esAgrupable(*n2)) || (n2->esAgrupable(*n))) {
					agrupacion[c].push_back(n->getMasFrecuente());
					agrupacion[c].push_back(n2->getMasFrecuente());
					it2 = ln1.erase(it2);
					sola = false;
				}
			}
		}

		for (std::list<EntidadNombrada>::iterator it3 = agrupacion[c].begin();
				it3 != agrupacion[c].end(); it3++) {
			en2 = *it3;
			for (std::list<EntidadNombrada>::iterator it4 =
					agrupacion[c].end(); it4 != agrupacion[c].begin(); it4--) {
				EntidadNombrada en3 = *it4;
				if ((en2.esIgual(en3)) && (distance(it3, it4) != 0)) {
					it4 = agrupacion[c].erase(it4);
				}
			}
		}
		if (sola) {
			agrupacion[c].push_back(n->getMasFrecuente());
			it1 = ln1.erase(it1);
		}

		c++;
	}

	for (unsigned int c = 0; c < ln1.size(); c++) {

		for (EntidadNombrada en : agrupacion[c]) {

			for (NoticiaIfPtr n : this->noticias) {

				if (n->getMasFrecuente().esIgual(en)) {
					if (agrupaciones == "") {
						agrupaciones = agrupaciones + "[" + n->getTitulo()
								+ "]\n";
					} else {
						agrupaciones = agrupaciones + "   *[" + n->getTitulo()
								+ "]\n";
					}
				}
			}
		}
		salida = salida + agrupaciones + "\n";
		agrupaciones = "";
	}

	return salida;
}
*/
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

bool Analizador::existe(std::list<EntidadNombrada> es,
		EntidadNombrada e) const {
	bool salida = false;
	EntidadNombrada aux;
	for (std::list<EntidadNombrada>::iterator it = es.begin(); it != es.end();
			it++) {
		aux = *it;
		if (aux.getEntidadNombrada().compare(e.getEntidadNombrada()) == 0) {
			salida = true;
		}
	}
	return salida;
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

