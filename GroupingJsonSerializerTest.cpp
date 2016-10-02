/*
 * GroupingSerializerTest.cpp
 *
 *  Created on: 2 Oct 2016
 *      Author: dancre
 */

#include <gmock/gmock.h>

#include <sstream>

#include "ItemAgrupableMock.h"
#include "JsonParser.h"
#include "GroupingJsonSerializer.h"

using testing::IsEmpty;
using testing::Eq;
using testing::StrEq;
using testing::ElementsAre;
using testing::Return;

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
