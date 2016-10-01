/*
 * TweetParser.h
 *
 *  Created on: 30 de sept. de 2016
 *      Author: dancre
 */

#ifndef TWEETPARSER_H_
#define TWEETPARSER_H_

#include <istream>
#include <string>
#include <memory>

#include "Tweet.h"

class CannotParseException : public std::exception {
public:
	const char* what() const throw() {
		return "Cannot parse file";
	}
};

class TweetParser {
private:
	std::istream& input;
	std::string stopListFile;
public:
	TweetParser(std::istream& inputStream, const std::string& stopListFile) :
		input(inputStream),
		stopListFile(stopListFile) {}
	std::list<std::shared_ptr<Tweet> > parse();
};

#endif /* TWEETPARSER_H_ */
