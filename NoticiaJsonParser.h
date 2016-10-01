/*
 * NoticiaJsonParser.h
 *
 *  Created on: 1 Oct 2016
 *      Author: dancre
 */

#ifndef NOTICIAJSONPARSER_H_
#define NOTICIAJSONPARSER_H_

#include "Noticia.h"

class NoticiaJsonParser {
public:
	NoticiaJsonParser(std::istream& inputStream, const std::string& stopListFile) {};
	Noticia parse();
};

#endif /* NOTICIAJSONPARSER_H_ */
