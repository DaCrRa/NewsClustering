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
#include "JsonParser.h"

class NoticiaJsonParser : public NoticiaParser {
public:
	NoticiaJsonParser(const std::string& stopListFile) :
		NoticiaParser(stopListFile) {};
	Noticia parse(std::istream& input);
};

#endif /* NOTICIAJSONPARSER_H_ */
