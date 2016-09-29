/*
 * Tweet.h
 *
 *  Created on: 29 de sept. de 2016
 *      Author: dancre
 */

#ifndef TWEET_H_
#define TWEET_H_

#include "ItemAgrupable.h"

class Tweet {
public:
	Tweet(int id,
			const std::string& usuario,
			const std::string& tweet,
			const std::string& palabrasReservadasFile) {}
	EntidadNombrada getMasFrecuente();
	std::list<EntidadNombrada> getEntidades() const;
	bool esAgrupablePorEntidadMasNombrada(ItemAgrupable& n) const;
	bool esAgrupablePorTematica(ItemAgrupable& n) const;
};

#endif /* TWEET_H_ */
