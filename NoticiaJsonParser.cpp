/*
 * NoticiaJsonParser.cpp
 *
 *  Created on: 1 Oct 2016
 *      Author: dancre
 */

#include "NoticiaJsonParser.h"

Noticia NoticiaJsonParser::parse() {
	return Noticia("Esto es el titulo de la noticia",
			"Esto es el primer parrafo del cuerpo de la noticia.\n" \
			"Esto es la segunda frase del cuerpo de la noticia",
			"stopList.txt");
}

