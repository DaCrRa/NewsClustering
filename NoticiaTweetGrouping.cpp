/*
 * NoticiaTweetGrouping.cpp
 *
 *  Created on: 29 de sept. de 2016
 *      Author: dancre
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ItemAgrupable.h"
#include "Noticia.h"
#include "Tweet.h"
#include "CriterioDeAgrupacion.h"
#include "PorEntidadMasNombrada.h"
#include "PorTematica.h"

TEST(NoticiaTweetGrouping, givenTweetAndNoticiaWithNoEntidadNombrada_whenCallingPorEntidadMasNombradaSonAgrupables_returnFalse) {
	std::shared_ptr<Noticia> noticia(new Noticia("el titular", "el cuerpo sin ninguna entidad nombrada", ""));
	std::shared_ptr<Tweet> tweet(new Tweet(0, "usuario", "el tweet tiene una Entidad nombrada", ""));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr itemNoticia(noticia);
	ItemAgrupablePtr itemTweet(tweet);
	ASSERT_FALSE(criterio->sonAgrupables(itemNoticia, itemTweet));
}

TEST(NoticiaTweetGrouping, givenTweetWithNoEntidadNombradaAndNoticia_whenCallingPorEntidadMasNombradaSonAgrupables_returnFalse) {
	std::shared_ptr<Noticia> noticia(new Noticia("el titular", "el cuerpo con una Entidad", ""));
	std::shared_ptr<Tweet> tweet(new Tweet(0, "usuario", "el tweet sin entidades", ""));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr itemNoticia(noticia);
	ItemAgrupablePtr itemTweet(tweet);
	ASSERT_FALSE(criterio->sonAgrupables(itemNoticia, itemTweet));

}

TEST(NoticiaTweetGrouping, givenTweetAndNoticiaDifferentEntidadMasNombrada_whenCallingPorEntidadMasNombradaSonAgrupables_returnFalse) {
	std::shared_ptr<Noticia> noticia(new Noticia("el titular", "el cuerpo con una Entidad pero la mas nombrada es Otra Otra Otra", ""));
	std::shared_ptr<Tweet> tweet(new Tweet(0, "usuario", "el tweet contiene Entidad Otra pero la mas nombrada es Distinta Distinta Distinta", ""));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr itemNoticia(noticia);
	ItemAgrupablePtr itemTweet(tweet);
	ASSERT_FALSE(criterio->sonAgrupables(itemNoticia, itemTweet));

}

TEST(NoticiaTweetGrouping, givenTweetAndNoticiaSameEntidadMasNombrada_whenCallingPorEntidadMasNombradaSonAgrupables_returnTrue) {
	std::shared_ptr<Noticia> noticia(new Noticia("el titular", "el cuerpo con una Entidad", ""));
	std::shared_ptr<Tweet> tweet(new Tweet(0, "usuario", "el tweet con la misma Entidad", ""));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr itemNoticia(noticia);
	ItemAgrupablePtr itemTweet(tweet);
	ASSERT_TRUE(criterio->sonAgrupables(itemNoticia, itemTweet));
}

TEST(NoticiaTweetGrouping, givenTweetAndNoticiaSameEntidadMasNombrada_whenCallingPorEntidadMasNombradaSonAgrupables_returnTrue_2) {
	std::shared_ptr<Noticia> noticia(new Noticia("el titular", "el cuerpo con una Entidad Entidad Otra Diferente", ""));
	std::shared_ptr<Tweet> tweet(new Tweet(0, "usuario", "el tweet con la misma Entidad Entidad Entidad Tercera", ""));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr itemNoticia(noticia);
	ItemAgrupablePtr itemTweet(tweet);
	ASSERT_TRUE(criterio->sonAgrupables(itemNoticia, itemTweet));
}

TEST(NoticiaTweetGrouping, givenTweetWithNoEntidadNombradaAndNoticia_whenCallingPorTematicaSonAgrupables_returnFalse) {
	std::shared_ptr<Noticia> noticia(new Noticia("el titular", "el cuerpo con una Entidad Entidad Otra Diferente", ""));
	std::shared_ptr<Tweet> tweet(new Tweet(0, "usuario", "el tweet sin entidad", ""));

	CriterioDeAgrupacionPtr criterio(new PorTematica());

	ItemAgrupablePtr itemNoticia(noticia);
	ItemAgrupablePtr itemTweet(tweet);
	ASSERT_FALSE(criterio->sonAgrupables(itemNoticia, itemTweet));
}

TEST(NoticiaTweetGrouping, givenTweetAndNoticiaWithNoEntidad_whenCallingPorTematicaSonAgrupables_returnFalse) {
	std::shared_ptr<Noticia> noticia(new Noticia("el titular", "el cuerpo sin niguna entidad", ""));
	std::shared_ptr<Tweet> tweet(new Tweet(0, "usuario", "el tweet con Entidades", ""));

	CriterioDeAgrupacionPtr criterio(new PorTematica());

	ItemAgrupablePtr itemNoticia(noticia);
	ItemAgrupablePtr itemTweet(tweet);
	ASSERT_FALSE(criterio->sonAgrupables(itemNoticia, itemTweet));
}

TEST(NoticiaTweetGrouping, givenNoticiaAndTweetWithEntidadNoMasNombrada_whenCallingPorTematicaSonAgrupables_returnFalse) {
	std::shared_ptr<Noticia> noticia(new Noticia("el titular", "el cuerpo con Entidad Mas Nombrada Nombrada Nombrada", ""));
	std::shared_ptr<Tweet> tweet(new Tweet(0, "usuario", "el tweet contiene Entidad", ""));

	CriterioDeAgrupacionPtr criterio(new PorTematica());

	ItemAgrupablePtr itemNoticia(noticia);
	ItemAgrupablePtr itemTweet(tweet);
	ASSERT_FALSE(criterio->sonAgrupables(itemNoticia, itemTweet));
}

TEST(NoticiaTweetGrouping, givenNoticiaAndTweetWithEntidadMasNombrada_whenCallingPorTematicaSonAgrupables_returnFalse) {
	std::shared_ptr<Noticia> noticia(new Noticia("el titular", "el cuerpo con Entidad Mas Nombrada Nombrada Nombrada", ""));
	std::shared_ptr<Tweet> tweet(new Tweet(0, "usuario", "el tweet contiene Entidad Nombrada", ""));

	CriterioDeAgrupacionPtr criterio(new PorTematica());

	ItemAgrupablePtr itemNoticia(noticia);
	ItemAgrupablePtr itemTweet(tweet);
	ASSERT_TRUE(criterio->sonAgrupables(itemNoticia, itemTweet));
}
