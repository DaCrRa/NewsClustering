/*
 * Tweet.h
 *
 *  Created on: 29 de sept. de 2016
 *      Author: dancre
 */

#ifndef TWEET_H_
#define TWEET_H_

#include "AbstractItemAgrupable.h"

class Tweet : public AbstractItemAgrupable {
public:
	Tweet(int id,
			const std::string& usuario,
			const std::string& tweet,
			const std::string& palabrasReservadasFile) :
			AbstractItemAgrupable(tweet, palabrasReservadasFile) {}

	std::string getTextoDestacado() const;
	bool esAgrupablePorTematica(ItemAgrupable& n) const;
	bool admiteAgrupacionPorCoincidenciaDeCualquierEntidad() const;
};

#endif /* TWEET_H_ */
