/*
 * Analizador.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef ANALIZADOR_H_
#define ANALIZADOR_H_
#include <string>
#include <list>

#include "NoticiaIf.h"

class Analizador {

	std::list<NoticiaIfPtr> noticias;
	std::string ruta;


public:
	Analizador();
	Analizador(std::string ruta);

	std::list<NoticiaIfPtr> getNoticias() const;
	void setNoticias(std::string ruta);
	void setNoticias(const std::list<NoticiaIfPtr>& noticias);

	std::list<std::list<NoticiaIfPtr> > agruparNoticiasPorEntidadMasFrecuente();
	std::list<std::list<NoticiaIfPtr> > agruparNoticiasPorTematica(const std::list<std::list<NoticiaIfPtr> >& preGrouped);

	std::string toString()const;

private:

	std::string rellenarCeros(int n, int size)const;
	void ordenarNoticias();

};

#endif /* ANALIZADOR_H_ */
