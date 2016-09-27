/*
 * NoticiaParser.cpp
 *
 *  Created on: 26 de sept. de 2016
 *      Author: dancre
 */

#include "NoticiaParser.h"

#include <sstream>
#include <algorithm>

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

Noticia NoticiaParser::parse() {
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

