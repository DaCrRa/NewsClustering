
#include <gmock/gmock.h>

#include "Tweet.h"
#include "TweetParser.h"

#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>

using testing::StrEq;
using testing::ElementsAre;
using testing::UnorderedElementsAre;
using testing::SizeIs;
using testing::IsEmpty;
using testing::Pointee;
using testing::IsEmpty;
using testing::Eq;

class TweetParserTest : public ::testing::Test {
public:
   static const std::string STOP_LIST_FILENAME;
protected:
   static void SetUpTestCase() {
      std::ofstream stopList(STOP_LIST_FILENAME);
      stopList << "EntidadExcluida" << std::endl;
   }

   static void TearDownTestCase() {
      remove(STOP_LIST_FILENAME.c_str());
   }
};
const std::string TweetParserTest::STOP_LIST_FILENAME = "stopList.txt";

TEST_F(TweetParserTest, givenParser_whenCallingParseWithJsonWithOneTweet_thenReturnsListWithOneTweetInstance) {
	std::string tweetsJson(
		"[" \
			"{" \
				"\"id\": 0," \
				"\"usuario\" : \"@pepe_perez\"," \
				"\"tuit\": \"Liberan a los dos sospechosos detenidos por el asesinato de un ni�o de 11 a�os en Liverpool Liverpool\"" \
			"}"\
		"]");

	std::stringstream input(tweetsJson);
	TweetParser parser(input, "stopList.txt");

	std::list<std::shared_ptr<Tweet> > parsedTweets = parser.parse();

	ASSERT_THAT(parsedTweets, SizeIs(1));

	ASSERT_THAT(parsedTweets.front()->getId(), Eq(0));
	ASSERT_THAT(parsedTweets.front()->getUsuario(), StrEq("@pepe_perez"));
	ASSERT_THAT(parsedTweets.front()->getTweet(), StrEq("Liberan a los dos sospechosos detenidos por el asesinato de un ni�o de 11 a�os en Liverpool Liverpool"));
	ASSERT_THAT(parsedTweets.front()->getTextoDestacado(), StrEq("Liberan a los dos sospechosos detenidos por el asesinato de un ni�o de 11 a�os en Liverpool Liverpool"));
	ASSERT_THAT(parsedTweets.front()->getEntidades(), UnorderedElementsAre(EntidadNombrada("Liberan", 1), EntidadNombrada("Liverpool", 2)));
	ASSERT_THAT(parsedTweets.front()->getMasFrecuente(), Eq(EntidadNombrada("Liverpool", 2)));
}

TEST_F(TweetParserTest, givenParser_whenCallingParseWithJsonWithOneTweet_thenReturnsListWithOneTweetInstance_2) {
	std::string tweetsJson(
		"[" \
			"{" \
				"\"id\": 1," \
				"\"usuario\" : \"@tomas_roncero\"," \
				"\"tuit\": \"Pepe debe renovar si o si\"" \
			"}"
		"]");

	std::stringstream input(tweetsJson);
	TweetParser parser(input, "stopList.txt");

	std::list<std::shared_ptr<Tweet> > parsedTweets = parser.parse();

	ASSERT_THAT(parsedTweets, SizeIs(1));

	ASSERT_THAT(parsedTweets.front()->getId(), Eq(1));
	ASSERT_THAT(parsedTweets.front()->getUsuario(), StrEq("@tomas_roncero"));
	ASSERT_THAT(parsedTweets.front()->getTweet(), StrEq("Pepe debe renovar si o si"));
	ASSERT_THAT(parsedTweets.front()->getTextoDestacado(), StrEq("Pepe debe renovar si o si"));
	ASSERT_THAT(parsedTweets.front()->getEntidades(), UnorderedElementsAre(EntidadNombrada("Pepe", 1)));
	ASSERT_THAT(parsedTweets.front()->getMasFrecuente(), Eq(EntidadNombrada("Pepe", 1)));
}

TEST_F(TweetParserTest, givenParser_whenCallingParseWithJsonWithTwoTweets_thenReturnsListWithTwoTweetInstances) {
	std::string tweetsJson(
		"[" \
			"{" \
				"\"id\": 0," \
				"\"usuario\" : \"@pepe_perez\"," \
				"\"tuit\": \"Liberan a los dos sospechosos detenidos por el asesinato de un ni�o de 11 a�os en Liverpool Liverpool\"" \
			"},"\
			"{" \
				"\"id\": 1," \
				"\"usuario\" : \"@tomas_roncero\"," \
				"\"tuit\": \"Pepe debe renovar si o si\"" \
			"}"
		"]");

	std::stringstream input(tweetsJson);
	TweetParser parser(input, "stopList.txt");

	std::list<std::shared_ptr<Tweet> > parsedTweets = parser.parse();

	ASSERT_THAT(parsedTweets, UnorderedElementsAre(
		Pointee(Tweet(0, "@pepe_perez", "Liberan a los dos sospechosos detenidos por el asesinato de un ni�o de 11 a�os en Liverpool Liverpool", "stopList.txt")),
		Pointee(Tweet(1, "@tomas_roncero", "Pepe debe renovar si o si", "stopList.txt"))
	));
}

TEST_F(TweetParserTest, givenParser_whenCallingParseWithJsonWithOneTweetWithPalabraReservada_thenReturnsListWithOneTweetInstance) {
	std::string tweetsJson(
		"[" \
			"{" \
				"\"id\": 0," \
				"\"usuario\" : \"@pepe_perez\"," \
				"\"tuit\": \"tuit con EntidadExcluida\"" \
			"}"\
		"]");

	std::stringstream input(tweetsJson);
	TweetParser parser(input, "stopList.txt");

	std::list<std::shared_ptr<Tweet> > parsedTweets = parser.parse();

	ASSERT_THAT(parsedTweets, SizeIs(1));

	ASSERT_THAT(parsedTweets.front()->getId(), Eq(0));
	ASSERT_THAT(parsedTweets.front()->getUsuario(), StrEq("@pepe_perez"));
	ASSERT_THAT(parsedTweets.front()->getTweet(), StrEq("tuit con EntidadExcluida"));
	ASSERT_THAT(parsedTweets.front()->getTextoDestacado(), StrEq("tuit con EntidadExcluida"));
	ASSERT_THAT(parsedTweets.front()->getEntidades(), IsEmpty());
	ASSERT_THROW(parsedTweets.front()->getMasFrecuente(), NoEntidadNombradaException);
}

TEST_F(TweetParserTest, givenParser_whenCallingParseWithBadJson_thenThrowsCannotParseException) {
	std::string tweetsJson(
		"[" \
			"{" \
				"\"id\": 0," \
				"\"usuario\" : \"@pepe_perez\"," \
				"\"tuit\": \"tuit con EntidadExcluida\"" \
		"]");

	std::stringstream input(tweetsJson);
	TweetParser parser(input, "stopList.txt");

	ASSERT_THROW(parser.parse(), CannotParseException);
}

TEST_F(TweetParserTest, givenParser_whenCallingParseEmptyJson_thenReturnsEmptyList) {
	std::string tweetsJson(
		"[]");

	std::stringstream input(tweetsJson);
	TweetParser parser(input, "stopList.txt");

	ASSERT_THAT(parser.parse(), IsEmpty());
}


TEST_F(TweetParserTest, givenParser_whenCallingParseEmptyJson_thenReturnsEmptyList_2) {
	std::string tweetsJson(
		"[{},{},{}]");

	std::stringstream input(tweetsJson);
	TweetParser parser(input, "stopList.txt");

	ASSERT_THAT(parser.parse(), IsEmpty());
}

TEST_F(TweetParserTest, givenParser_whenCallingParseJsonTweetMissingIdField_thenReturnsEmptyList) {
	std::string tweetsJson(
			"[" \
				"{" \
					"\"id_missing_field\": 0," \
					"\"usuario\" : \"@pepe_perez\"," \
					"\"tuit\": \"Liberan a los dos sospechosos detenidos por el asesinato de un ni�o de 11 a�os en Liverpool Liverpool\"" \
				"}"\
			"]");

	std::stringstream input(tweetsJson);
	TweetParser parser(input, "stopList.txt");

	ASSERT_THAT(parser.parse(), IsEmpty());
}

TEST_F(TweetParserTest, givenParser_whenCallingParseJsonTweetMissingUsuarioField_thenReturnsEmptyList) {
	std::string tweetsJson(
			"[" \
				"{" \
					"\"id\": 0," \
					"\"missing_usuario\" : \"@pepe_perez\"," \
					"\"tuit\": \"Liberan a los dos sospechosos detenidos por el asesinato de un ni�o de 11 a�os en Liverpool Liverpool\"" \
				"}"\
			"]");

	std::stringstream input(tweetsJson);
	TweetParser parser(input, "stopList.txt");

	ASSERT_THAT(parser.parse(), IsEmpty());
}

TEST_F(TweetParserTest, givenParser_whenCallingParseJsonTweetMissingTweetField_thenReturnsEmptyList) {
	std::string tweetsJson(
			"[" \
				"{" \
					"\"id_missing_field\": 0," \
					"\"usuario\" : \"@pepe_perez\"," \
					"\"tuit_missing\": \"Liberan a los dos sospechosos detenidos por el asesinato de un ni�o de 11 a�os en Liverpool Liverpool\"" \
				"}"\
			"]");

	std::stringstream input(tweetsJson);
	TweetParser parser(input, "stopList.txt");

	ASSERT_THAT(parser.parse(), IsEmpty());
}
