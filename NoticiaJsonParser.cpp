/*
 * NoticiaJsonParser.cpp
 *
 *  Created on: 1 Oct 2016
 *      Author: dancre
 */

#include "NoticiaJsonParser.h"

#include "JsonParser.h"

Noticia NoticiaJsonParser::parse(std::istream& input) {
	Json::Value noticiaJson = JsonParser(input).parse();

	std::string titulo(noticiaJson["titulo"].asString());
	if (titulo.empty()) {
		throw NoticiaInvalidaException();
	}

	std::string cuerpo;
	for(auto& parrafoJson : noticiaJson["parrafos"]) {
		cuerpo += parrafoJson.asString();
		cuerpo += "\n";
	}
	cuerpo = trim(cuerpo);
	return Noticia(
			titulo,
			cuerpo,
			stopListFilename);
}

