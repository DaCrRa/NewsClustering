/*
 * NoticiaParser.cpp
 *
 *  Created on: 26 de sept. de 2016
 *      Author: dancre
 */

#include "NoticiaParser.h"

#include <sstream>

Noticia NoticiaParser::parse() {
	std::string titulo;
	std::getline(input, titulo);
	std::string cuerpo(std::istreambuf_iterator<char>(input), {});
	return Noticia(titulo, cuerpo, stopListFilename);
}
