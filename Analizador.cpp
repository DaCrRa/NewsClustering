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
	std::list<std::list<NoticiaIfPtr> > groups;

	std::list<NoticiaIfPtr> noticiasNoProcesadas = this->noticias;

	while (!noticiasNoProcesadas.empty()) {
		std::list<NoticiaIfPtr> nuevoGrupo;
		NoticiaIfPtr noticiaDeReferencia(noticiasNoProcesadas.front());
		noticiasNoProcesadas.pop_front();
		nuevoGrupo.push_back(noticiaDeReferencia);
		std::function<bool(NoticiaIfPtr&)> agrupacionPorEntidadMasNombrada([&](NoticiaIfPtr& n2) -> bool {
			return puedenAgruparsePorEntidadMasNombrada(noticiaDeReferencia, n2);
		});
		std::list<NoticiaIfPtr>::iterator it = encontrarNoticiaAgrupableCon(noticiaDeReferencia,
				noticiasNoProcesadas,
				agrupacionPorEntidadMasNombrada);
		while (it != noticiasNoProcesadas.end()) {
			nuevoGrupo.push_back(*it);
			it = noticiasNoProcesadas.erase(it);
			it = encontrarNoticiaAgrupableCon(noticiaDeReferencia,
					noticiasNoProcesadas,
					agrupacionPorEntidadMasNombrada);
		}
		groups.push_back(nuevoGrupo);
	}

	return groups;
}

std::list<std::list<NoticiaIfPtr> > Analizador::agruparNoticiasPorTematica(const std::list<std::list<NoticiaIfPtr> >& preGrouped) {
	std::list<std::list<NoticiaIfPtr> > outputGroups;
	std::list<std::list<NoticiaIfPtr> > remainingGroups(preGrouped);

	while (!remainingGroups.empty()) {
		std::list<NoticiaIfPtr> group(remainingGroups.front());
		remainingGroups.pop_front();
		outputGroups.push_back(group);
		auto& lastOutputGroup = outputGroups.back();
		for (NoticiaIfPtr noticia : lastOutputGroup) {
			auto groupableGroupIt = encontrarGrupoAgrupableCon(noticia, remainingGroups);
			while (groupableGroupIt != remainingGroups.end()) {
				lastOutputGroup.insert(lastOutputGroup.end(),
						groupableGroupIt->begin(),
						groupableGroupIt->end());
				remainingGroups.erase(groupableGroupIt);
				groupableGroupIt = encontrarGrupoAgrupableCon(noticia, remainingGroups);
			}
		}

	}
	return outputGroups;
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

bool Analizador::puedenAgruparsePorEntidadMasNombrada(NoticiaIfPtr n1, NoticiaIfPtr n2) {
	return n1->esAgrupablePorEntidadMasNombrada(*n2) || n2->esAgrupablePorEntidadMasNombrada(*n1);
}

bool Analizador::puedenAgruparsePorTema(NoticiaIfPtr n1, NoticiaIfPtr n2) {
	return n1->esAgrupablePorTematica(*n2) || n2->esAgrupablePorTematica(*n1);
}

std::list<NoticiaIfPtr>::iterator Analizador::encontrarNoticiaAgrupableCon(NoticiaIfPtr n1,
		std::list<NoticiaIfPtr>& noticias,
		std::function<bool(NoticiaIfPtr&)>& criterioAgrupacion) {

	auto it = std::find_if(
			noticias.begin(),
			noticias.end(),
			criterioAgrupacion
	);
	return it;
}

std::list<std::list<NoticiaIfPtr> >::iterator Analizador::encontrarGrupoAgrupableCon(NoticiaIfPtr n1, std::list<std::list<NoticiaIfPtr> >& grupos) {
	std::function<bool(NoticiaIfPtr&)> agrupacionPorTema([&](NoticiaIfPtr& n2) -> bool {
		return puedenAgruparsePorTema(n1, n2);
	});
	return std::find_if(
			grupos.begin(),
			grupos.end(),
			[&](std::list<NoticiaIfPtr>& grupo) -> bool {
				return encontrarNoticiaAgrupableCon(n1, grupo, agrupacionPorTema) != grupo.end();
			}
	);
}
