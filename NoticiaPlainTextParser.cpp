/*
 * NoticiaParser.cpp
 *
 *  Created on: 26 de sept. de 2016
 *      Author: dancre
 */

#include "NoticiaPlainTextParser.h"

#include <sstream>

Noticia NoticiaPlainTextParser::parse() {
	std::string titulo;
	while (titulo.empty() && input.good()) {
		std::getline(input, titulo);
		titulo = trim(titulo);
	}
	if (titulo.empty()) {
		throw NoticiaInvalidaException();
	}
	std::string cuerpo(std::istreambuf_iterator<char>(input), {});
	cuerpo = trim(cuerpo);
	return Noticia(titulo, cuerpo, stopListFilename);
}

