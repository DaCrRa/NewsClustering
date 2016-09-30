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

class TweetParser {
public:
	TweetParser(std::istream& inputStream, const std::string& stopListFile) {}
	std::list<std::shared_ptr<Tweet> > parse();
};

#endif /* TWEETPARSER_H_ */
