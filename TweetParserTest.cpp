
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

TEST_F(TweetParserTest, givenParser_whenCallingParse_thenReturnsNoticiaInstance) {
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
