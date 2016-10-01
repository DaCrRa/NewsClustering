/*
 * TweetParser.cpp
 *
 *  Created on: 30 de sept. de 2016
 *      Author: dancre
 */

#include "TweetParser.h"

std::list<std::shared_ptr<Tweet> > TweetParser::parse() {
		return std::list<std::shared_ptr<Tweet> >({
			std::shared_ptr<Tweet>(new Tweet(
					0,
					"",
					"Liberan a los dos sospechosos detenidos por el asesinato de un ni�o de 11 a�os en Liverpool Liverpool",
					""
				)
			)
		});
}
