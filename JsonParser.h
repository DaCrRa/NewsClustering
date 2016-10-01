/*
 * JsonParser.h
 *
 *  Created on: 1 Oct 2016
 *      Author: dancre
 */

#ifndef JSONPARSER_H_
#define JSONPARSER_H_

#include <istream>

#include <json/json.h>

class CannotParseException : public std::exception {
public:
	const char* what() const throw() {
		return "Cannot parse file";
	}
};

class JsonParser {
private:
	std::istream& input;
public:
	JsonParser(std::istream& input) :
		input(input) {};
	Json::Value parse();
};

#endif /* JSONPARSER_H_ */
#include <istream>
