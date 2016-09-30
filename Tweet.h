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
private:
	std::string tweet;
	bool contieneEntidadMasFrecuenteDe(ItemAgrupable& n) const;
	bool comparteAlgunaEntidadCon(ItemAgrupable& n) const;
public:
	Tweet(int id,
			const std::string& usuario,
			const std::string& t,
			const std::string& palabrasReservadasFile) :
			AbstractItemAgrupable(t, palabrasReservadasFile),
			tweet(t) {}

	int getId();
	std::string getUsuario();
	std::string getTweet();
	std::string getTextoDestacado() const;
	bool esAgrupablePorTematica(ItemAgrupable& n) const;
	bool admiteAgrupacionPorCoincidenciaDeCualquierEntidad() const;
};

#endif /* TWEET_H_ */
