/*
 * JsonParser.cpp
 *
 *  Created on: 1 Oct 2016
 *      Author: dancre
 */

#include "JsonParser.h"

Json::Value JsonParser::parse() {
	Json::Value parsedJson;
	try {
		input >> parsedJson;
	} catch (...) {
		throw CannotParseException();
	}
	return parsedJson;
}

