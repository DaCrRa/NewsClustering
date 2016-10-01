/*
 * NoticiaParser.h
 *
 *  Created on: 26 de sept. de 2016
 *      Author: dancre
 */

#ifndef SOURCE_DIRECTORY__NOTICIAPARSER_H_
#define SOURCE_DIRECTORY__NOTICIAPARSER_H_

#include "Noticia.h"
#include "NoticiaParser.h"

#include <istream>
#include <string>
#include <memory>

class NoticiaPlainTextParser : public NoticiaParser {
public:
	NoticiaPlainTextParser(std::istream& inputStream, const std::string& stopListFile) :
		NoticiaParser(inputStream, stopListFile) {};
	Noticia parse();
};

#endif /* SOURCE_DIRECTORY__NOTICIAPARSER_H_ */

