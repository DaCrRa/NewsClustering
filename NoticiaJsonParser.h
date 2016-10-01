/*
 * NoticiaJsonParser.h
 *
 *  Created on: 1 Oct 2016
 *      Author: dancre
 */

#ifndef NOTICIAJSONPARSER_H_
#define NOTICIAJSONPARSER_H_

#include "Noticia.h"
#include "NoticiaParser.h"

class NoticiaJsonParser : public NoticiaParser {
public:
	NoticiaJsonParser(std::istream& input, const std::string& stopListFile) :
		NoticiaParser(input, stopListFile) {};
	Noticia parse();
};

#endif /* NOTICIAJSONPARSER_H_ */
