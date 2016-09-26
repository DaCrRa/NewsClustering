/*
 * NoticiaParser.cpp
 *
 *  Created on: 26 de sept. de 2016
 *      Author: dancre
 */

#include "NoticiaParser.h"

Noticia NoticiaParser::parse() {
	return Noticia("Esto es el titulo de la noticia",
		"Esto es el primer parrafo del cuerpo de la noticia.\n"\
		"Esto es la segunda frase del cuerpo de la noticia", stopListFilename);
}
