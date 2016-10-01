/*
 * TweetParser.cpp
 *
 *  Created on: 30 de sept. de 2016
 *      Author: dancre
 */

#include "TweetParser.h"

std::list<std::shared_ptr<Tweet> > TweetParser::parse() {
	try {
		Json::Value jsontuits;
		input >> jsontuits;

		std::list<std::shared_ptr<Tweet> > parsedTweets;

		for(auto& jsontuit : jsontuits) {
			try {
				parsedTweets.push_back(std::shared_ptr<Tweet>(new Tweet(
						extractMandatoryFieldFrom(jsontuit, "id").asInt(),
						extractMandatoryFieldFrom(jsontuit, "usuario").asString(),
						extractMandatoryFieldFrom(jsontuit, "tuit").asString(),
						stopListFile
				)));
			} catch (MissingTweetFieldException& e) {
				// Skip this tweet, continue with the next one
			}
		}
		return parsedTweets;
	} catch (...) {
		throw CannotParseException();
	}
}

Json::Value TweetParser::extractMandatoryFieldFrom(const Json::Value& jsonTuit, const std::string& fieldName) {
	Json::Value jsonVal(jsonTuit[fieldName]);
	if (jsonVal.isNull()) {
		throw MissingTweetFieldException(fieldName);
	}
	return jsonVal;
}
