/*
 * NoticiaJsonParser.cpp
 *
 *  Created on: 1 Oct 2016
 *      Author: dancre
 */

#include "NoticiaJsonParser.h"

#include <json/json.h>

Noticia NoticiaJsonParser::parse() {
	Json::Value noticiaJson = parser.parse();

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

