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

#include <json/json.h>

#include "Tweet.h"

class CannotParseException : public std::exception {
public:
	const char* what() const throw() {
		return "Cannot parse file";
	}
};

class MissingTweetFieldException : public std::exception {
private:
	std::string missingFieldName;
public:
	MissingTweetFieldException(const std::string& fieldName) :
		missingFieldName(fieldName) {}
	const char* what() const throw() {
		return std::string("Missing field in tweet json: ").append(missingFieldName).c_str();
	}
};

class TweetParser {
private:
	std::istream& input;
	std::string stopListFile;
	Json::Value extractMandatoryFieldFrom(const Json::Value& jsonTuit, const std::string& fieldName);
public:
	TweetParser(std::istream& inputStream, const std::string& stopListFile) :
		input(inputStream),
		stopListFile(stopListFile) {}
	std::list<std::shared_ptr<Tweet> > parse();
};

#endif /* TWEETPARSER_H_ */
