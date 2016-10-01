/*
 * TweetParser.cpp
 *
 *  Created on: 30 de sept. de 2016
 *      Author: dancre
 */

#include "TweetParser.h"

#include <json/json.h>

std::list<std::shared_ptr<Tweet> > TweetParser::parse() {
	try {
		Json::Value jsontuits;
		input >> jsontuits;

		std::list<std::shared_ptr<Tweet> > parsedTweets;

		for(auto& jsontuit : jsontuits) {
			Json::Value idJsonVal(jsontuit["id"]);
			Json::Value usuarioJsonVal(jsontuit["usuario"].asString());
			Json::Value tuitJsonVal(jsontuit["tuit"].asString());
			if (idJsonVal.isNull() || usuarioJsonVal.isNull() || tuitJsonVal.isNull()) {
				continue;
			}
			parsedTweets.push_back(std::shared_ptr<Tweet>(new Tweet(
					idJsonVal.asInt(),
					usuarioJsonVal.asString(),
					tuitJsonVal.asString(),
					stopListFile
			)));
		}
		return parsedTweets;
	} catch (...) {
		throw CannotParseException();
	}
}
