/*
 * NoticiaTweetGrouping.cpp
 *
 *  Created on: 29 de sept. de 2016
 *      Author: dancre
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ItemAgrupable.h"
#include "Tweet.h"
#include "CriterioDeAgrupacion.h"
#include "PorEntidadMasNombrada.h"
#include "PorTematica.h"

TEST(TweetGrouping, givenTweetsWithNoEntidadNombrada_whenCallingPorEntidadMasNombradaSonAgrupables_returnFalse) {
	std::shared_ptr<Tweet> tweet1(new Tweet(0, "usuario", "el tweet no tiene entidades", ""));
	std::shared_ptr<Tweet> tweet2(new Tweet(0, "usuario", "el tweet no tiene entidades", ""));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr itemTweet1(tweet1);
	ItemAgrupablePtr itemTweet2(tweet2);
	ASSERT_FALSE(criterio->sonAgrupables(itemTweet1, itemTweet2));
}

TEST(TweetGrouping, givenTwoTweetsOneWithEntidadNombrada_whenCallingPorEntidadMasNombradaSonAgrupables_returnFalse) {
	std::shared_ptr<Tweet> tweet1(new Tweet(0, "usuario", "el tweet no tiene entidades", ""));
	std::shared_ptr<Tweet> tweet2(new Tweet(0, "usuario", "el tweet tiene una Entidad", ""));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr itemTweet1(tweet1);
	ItemAgrupablePtr itemTweet2(tweet2);
	ASSERT_FALSE(criterio->sonAgrupables(itemTweet1, itemTweet2));
}

TEST(TweetGrouping, givenTwoTweetsWithDifferentEntidadMasNombrada_whenCallingPorEntidadMasNombradaSonAgrupables_returnFalse) {
	std::shared_ptr<Tweet> tweet1(new Tweet(0, "usuario", "el cuerpo con una Entidad pero la mas nombrada es Otra Otra Otra", ""));
	std::shared_ptr<Tweet> tweet2(new Tweet(0, "usuario", "el tweet contiene Entidad Otra pero la mas nombrada es Distinta Distinta Distinta", ""));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr itemTweet1(tweet1);
	ItemAgrupablePtr itemTweet2(tweet2);
	ASSERT_FALSE(criterio->sonAgrupables(itemTweet1, itemTweet2));
}

TEST(TweetGrouping, givenTwoTweetSameEntidadMasNombrada_whenCallingPorEntidadMasNombradaSonAgrupables_returnTrue) {
	std::shared_ptr<Tweet> tweet1(new Tweet(0, "usuario", "el cuerpo con una Entidad", ""));
	std::shared_ptr<Tweet> tweet2(new Tweet(0, "usuario", "el tweet contiene Entidad", ""));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr itemTweet1(tweet1);
	ItemAgrupablePtr itemTweet2(tweet2);
	ASSERT_TRUE(criterio->sonAgrupables(itemTweet1, itemTweet2));
}

TEST(TweetGrouping, givenTwoTweetSameEntidadMasNombrada_whenCallingPorEntidadMasNombradaSonAgrupables_returnTrue_2) {
	std::shared_ptr<Tweet> tweet1(new Tweet(0, "usuario", "el cuerpo con una Entidad Entidad Otra Diferente", ""));
	std::shared_ptr<Tweet> tweet2(new Tweet(0, "usuario", "el tweet con la misma Entidad Entidad Entidad Tercera", ""));

	CriterioDeAgrupacionPtr criterio(new PorEntidadMasNombrada());

	ItemAgrupablePtr itemTweet1(tweet1);
	ItemAgrupablePtr itemTweet2(tweet2);
	ASSERT_TRUE(criterio->sonAgrupables(itemTweet1, itemTweet2));
}

TEST(TweetGrouping, givenTwoTweetWithNoEntidadNombrada_whenCallingPorTematicaSonAgrupables_returnFalse) {
	std::shared_ptr<Tweet> tweet1(new Tweet(0, "usuario", "el cuerpo sin entidad", ""));
	std::shared_ptr<Tweet> tweet2(new Tweet(0, "usuario", "el tweet sin entidad", ""));

	CriterioDeAgrupacionPtr criterio(new PorTematica());

	ItemAgrupablePtr itemTweet1(tweet1);
	ItemAgrupablePtr itemTweet2(tweet2);
	ASSERT_FALSE(criterio->sonAgrupables(itemTweet1, itemTweet2));
}

TEST(TweetGrouping, givenTwoTweetNotSharingEntidad_whenCallingPorTematicaSonAgrupables_returnFalse) {
	std::shared_ptr<Tweet> tweet1(new Tweet(0, "usuario", "el cuerpo con Entidad1", ""));
	std::shared_ptr<Tweet> tweet2(new Tweet(0, "usuario", "el tweet con Entidad2", ""));

	CriterioDeAgrupacionPtr criterio(new PorTematica());

	ItemAgrupablePtr itemTweet1(tweet1);
	ItemAgrupablePtr itemTweet2(tweet2);
	ASSERT_FALSE(criterio->sonAgrupables(itemTweet1, itemTweet2));
}

TEST(TweetGrouping, givenTwoTweetsSharingEntidad_whenCallingPorTematicaSonAgrupables_returnTrue) {
	std::shared_ptr<Tweet> tweet1(new Tweet(0, "usuario", "el cuerpo con Entidad Mas Nombrada Nombrada Nombrada", ""));
	std::shared_ptr<Tweet> tweet2(new Tweet(0, "usuario", "el tweet con Entidad Diferente Diferente", ""));

	CriterioDeAgrupacionPtr criterio(new PorTematica());

	ItemAgrupablePtr itemTweet1(tweet1);
	ItemAgrupablePtr itemTweet2(tweet2);
	ASSERT_TRUE(criterio->sonAgrupables(itemTweet1, itemTweet2));
}
