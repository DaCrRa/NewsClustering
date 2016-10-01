/*
 * NoticiaJsonParser.cpp
 *
 *  Created on: 1 Oct 2016
 *      Author: dancre
 */

#include "NoticiaJsonParser.h"

#include <algorithm>

#include <json/json.h>

// trim from beginning
static inline std::string& ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string& rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string& trim(std::string &s) {
    return ltrim(rtrim(s));
}

Noticia NoticiaJsonParser::parse() {
	Json::Value noticiaJson;
	inputStream >> noticiaJson;

	std::string titulo(noticiaJson["titulo"].asString());

	std::string cuerpo;
	for(auto& parrafoJson : noticiaJson["parrafos"]) {
		cuerpo += parrafoJson.asString();
		cuerpo += "\n";
	}
	cuerpo = trim(cuerpo);
	return Noticia(
			titulo,
			cuerpo,
			stopList);
}

