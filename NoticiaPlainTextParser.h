/*
 * NoticiaParser.h
 *
 *  Created on: 26 de sept. de 2016
 *      Author: dancre
 */

#ifndef SOURCE_DIRECTORY__NOTICIAPARSER_H_
#define SOURCE_DIRECTORY__NOTICIAPARSER_H_

#include "Noticia.h"

#include <istream>
#include <string>
#include <memory>

class NoticiaInvalidaException : public std::exception {
public:
	const char* what() const throw() {
		return "No puede instanciarse una noticia a partir de la entrada especificada";
	}
};

class NoticiaPlainTextParser {
private:
	std::istream& input;
	std::string stopListFilename;
public:
	NoticiaPlainTextParser(std::istream& inputStream, const std::string& stopListFile) :
		input(inputStream),
		stopListFilename(stopListFile) {};
	Noticia parse();
};

#endif /* SOURCE_DIRECTORY__NOTICIAPARSER_H_ */

