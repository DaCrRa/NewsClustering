/*
 * NoticiaParser.cpp
 *
 *  Created on: 26 de sept. de 2016
 *      Author: dancre
 */

#include "NoticiaPlainTextParser.h"

#include <sstream>

Noticia NoticiaPlainTextParser::parse(std::istream& inputStream) {
	std::string titulo;
	while (titulo.empty() && inputStream.good()) {
		std::getline(inputStream, titulo);
		titulo = trim(titulo);
	}
	if (titulo.empty()) {
		throw NoticiaInvalidaException();
	}
	std::string cuerpo(std::istreambuf_iterator<char>(inputStream), {});
	cuerpo = trim(cuerpo);
	return Noticia(titulo, cuerpo, stopListFilename);
}

