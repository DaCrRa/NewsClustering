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

class NoticiaParser {
private:
	std::string stopListFilename;
public:
	NoticiaParser(const std::istream& inputStream, const std::string& stopListFile) :
		stopListFilename(stopListFile) {};
	Noticia parse();
};

#endif /* SOURCE_DIRECTORY__NOTICIAPARSER_H_ */

