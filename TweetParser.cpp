/*
 * TweetParser.cpp
 *
 *  Created on: 30 de sept. de 2016
 *      Author: dancre
 */

#include "TweetParser.h"

#include <json/json.h>

std::list<std::shared_ptr<Tweet> > TweetParser::parse() {

	Json::Value jsontuits;
	input >> jsontuits;

	std::list<std::shared_ptr<Tweet> > parsedTweets;
	for(Json::Value::const_iterator tuitIt = jsontuits.begin(); tuitIt != jsontuits.end(); ++tuitIt) {
		parsedTweets.push_back(std::shared_ptr<Tweet>(new Tweet(
				(*tuitIt)["id"].asInt(),
				(*tuitIt)["usuario"].asString(),
				(*tuitIt)["tuit"].asString(),
				""
		)));
	}
	return parsedTweets;
}
