/*
 * GroupingSerializerTest.cpp
 *
 *  Created on: 2 Oct 2016
 *      Author: dancre
 */

#include <gmock/gmock.h>

#include <sstream>
#include <algorithm>
#include <ostream>

#include "ItemAgrupableMock.h"
#include "JsonParser.h"
#include "GroupingJsonSerializer.h"

using testing::IsEmpty;
using testing::Eq;
using testing::StrEq;
using testing::ElementsAre;
using testing::Return;
using testing::Matches;


MATCHER_P(JsonArrayContainsString, s, "") {
	return std::find_if(
			arg.begin(),
			arg.end(),
			[&](const Json::Value& v) -> bool {
				return v.asString() == s;
			}
	) != arg.end();
}

MATCHER_P2(JsonArrayContainsStrings, s1, s2, "") {
	return Matches(JsonArrayContainsString(s1))(arg) &&
			Matches(JsonArrayContainsString(s2))(arg);
}

MATCHER_P(JsonArrayContainsArray, matcher, "") {
	return std::find_if(
			arg.begin(),
			arg.end(),
			Matches(matcher)
	) != arg.end();
}

TEST(GroupingJsonSerializerTest, givenEmptyGrouping_whenCallingSerialize_thenReturnsEmptyJsonArray) {
	std::list<std::list<ItemAgrupablePtr> > grouping;
	std::ostringstream serializerOutputStream;

	GroupingJsonSerializer serializer;
	serializer.serialize(grouping, serializerOutputStream);

	std::istringstream inputForParser(serializerOutputStream.str());
	JsonParser p(inputForParser);
	Json::Value parsedGrouping = p.parse();
	ASSERT_THAT(parsedGrouping, IsEmpty());
}

TEST(GroupingJsonSerializerTest, givenGroupingWithEmptyGroups_whenCallingSerialize_thenReturnsEmptyJsonArray) {
	std::list<std::list<ItemAgrupablePtr> > grouping({
		std::list<ItemAgrupablePtr>(),
		std::list<ItemAgrupablePtr>()
	});
	std::ostringstream serializerOutputStream;

	GroupingJsonSerializer serializer;
	serializer.serialize(grouping, serializerOutputStream);

	std::istringstream inputForParser(serializerOutputStream.str());
	JsonParser p(inputForParser);
	Json::Value parsedGrouping = p.parse();
	ASSERT_THAT(parsedGrouping, IsEmpty());
}

TEST(GroupingJsonSerializerTest, givenGroupinWithOneGroupAndOneEmptyGroup_whenCallingSerialize_thenReturnsJsonWithOneGroup) {
	std::shared_ptr<ItemAgrupableMock> item(new ItemAgrupableMock());
	EXPECT_CALL(*item, getTextoDestacado()).WillRepeatedly(Return("texto destacado"));
	std::list<std::list<ItemAgrupablePtr> > grouping({
		std::list<ItemAgrupablePtr>({ItemAgrupablePtr(item)}),
		std::list<ItemAgrupablePtr>()
	});
	std::ostringstream serializerOutputStream;

	GroupingJsonSerializer serializer;
	serializer.serialize(grouping, serializerOutputStream);

	std::istringstream inputForParser(serializerOutputStream.str());
	JsonParser p(inputForParser);
	Json::Value parsedGrouping = p.parse();
	ASSERT_THAT(parsedGrouping.size(), Eq(1));
	ASSERT_THAT(parsedGrouping[0].size(), Eq(1));
	ASSERT_THAT(parsedGrouping[0][0].asString(), StrEq("texto destacado"));
}

TEST(GroupingJsonSerializerTest, givenGroupinWithOneGroupTwoItems_whenCallingSerialize_thenReturnsJsonWithOneGroup) {
	std::shared_ptr<ItemAgrupableMock> item1(new ItemAgrupableMock());
	std::shared_ptr<ItemAgrupableMock> item2(new ItemAgrupableMock());
	EXPECT_CALL(*item1, getTextoDestacado()).WillRepeatedly(Return("texto destacado 1"));
	EXPECT_CALL(*item2, getTextoDestacado()).WillRepeatedly(Return("texto destacado 2"));
	std::list<std::list<ItemAgrupablePtr> > grouping({
		std::list<ItemAgrupablePtr>({
			ItemAgrupablePtr(item1),
			ItemAgrupablePtr(item2)
		})
	});
	std::ostringstream serializerOutputStream;

	GroupingJsonSerializer serializer;
	serializer.serialize(grouping, serializerOutputStream);

	std::istringstream inputForParser(serializerOutputStream.str());
	JsonParser p(inputForParser);
	Json::Value parsedGrouping = p.parse();
	ASSERT_THAT(parsedGrouping.size(), Eq(1));
	ASSERT_THAT(parsedGrouping[0].size(), Eq(2));
	ASSERT_THAT(parsedGrouping, JsonArrayContainsArray(JsonArrayContainsStrings("texto destacado 1", "texto destacado 2")));
}

TEST(GroupingJsonSerializerTest, givenGroupinWithTwoGroupaTwoItems_whenCallingSerialize_thenReturnsJsonWithTwoGroup) {
	std::shared_ptr<ItemAgrupableMock> item11(new ItemAgrupableMock());
	std::shared_ptr<ItemAgrupableMock> item12(new ItemAgrupableMock());
	std::shared_ptr<ItemAgrupableMock> item21(new ItemAgrupableMock());
	std::shared_ptr<ItemAgrupableMock> item22(new ItemAgrupableMock());
	EXPECT_CALL(*item11, getTextoDestacado()).WillRepeatedly(Return("primer item del grupo 1"));
	EXPECT_CALL(*item12, getTextoDestacado()).WillRepeatedly(Return("segundo item del primer grupo"));
	EXPECT_CALL(*item21, getTextoDestacado()).WillRepeatedly(Return("item 1 del segundo tema"));
	EXPECT_CALL(*item22, getTextoDestacado()).WillRepeatedly(Return("otro item hablando del segundo tema"));
	std::list<std::list<ItemAgrupablePtr> > grouping({
		std::list<ItemAgrupablePtr>({
			ItemAgrupablePtr(item11),
			ItemAgrupablePtr(item12)
		}),
		std::list<ItemAgrupablePtr>({
			ItemAgrupablePtr(item21),
			ItemAgrupablePtr(item22)
		})
	});
	std::ostringstream serializerOutputStream;

	GroupingJsonSerializer serializer;
	serializer.serialize(grouping, serializerOutputStream);

	std::istringstream inputForParser(serializerOutputStream.str());
	JsonParser p(inputForParser);
	Json::Value parsedGrouping = p.parse();
	ASSERT_THAT(parsedGrouping.size(), Eq(2));
	ASSERT_THAT(parsedGrouping, JsonArrayContainsArray(JsonArrayContainsStrings("segundo item del primer grupo", "primer item del grupo 1")));
	ASSERT_THAT(parsedGrouping, JsonArrayContainsArray(JsonArrayContainsStrings("item 1 del segundo tema", "otro item hablando del segundo tema")));
}
