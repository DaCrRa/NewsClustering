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
private:
	std::istream& inputStream;
	const std::string stopList;
public:
	NoticiaJsonParser(std::istream& input, const std::string& stopListFile) :
		inputStream(input),
		stopList(stopListFile) {};
	Noticia parse();
};

#endif /* NOTICIAJSONPARSER_H_ */
