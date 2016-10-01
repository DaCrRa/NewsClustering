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

#include "JsonParser.h"
#include "Tweet.h"

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

class WrongIdFieldException : public std::exception {
private:
	std::string wrongIdValue;
public:
	WrongIdFieldException(const std::string& idValue) :
		wrongIdValue(idValue) {}
	const char* what() const throw() {
		return std::string("Wrong id field value: ").append(wrongIdValue).c_str();
	}
};

class TweetParser {
private:
	JsonParser parser;
	std::string stopListFile;
	Json::Value extractMandatoryFieldFrom(const Json::Value& jsonTuit, const std::string& fieldName);
	int asInt(const Json::Value& jsonTuitId);
public:
	TweetParser(std::istream& inputStream, const std::string& stopListFile) :
		parser(inputStream),
		stopListFile(stopListFile) {}
	std::list<std::shared_ptr<Tweet> > parse();
};

#endif /* TWEETPARSER_H_ */
