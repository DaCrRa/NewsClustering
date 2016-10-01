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

	for(auto& jsontuit : jsontuits) {
		parsedTweets.push_back(std::shared_ptr<Tweet>(new Tweet(
				jsontuit["id"].asInt(),
				jsontuit["usuario"].asString(),
				jsontuit["tuit"].asString(),
				stopListFile
		)));
	}
	return parsedTweets;
}
