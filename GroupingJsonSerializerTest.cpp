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

TEST(GroupingJsonSerializerTest, givenEmptyGrouping_whenCallingSerialize_thenReturnsEmptyJsonArray) {
	std::list<std::list<ItemAgrupablePtr> > grouping;
	std::ostringstream serializerOutputStream;

	GroupingJsonSerializer serializer;
	serializer.serialize(grouping, serializerOutputStream);

	std::istringstream inputForParser(serializerOutputStream.str());
	JsonParser p(inputForParser);
	Json::Value parsedGrouping = p.parse();
	ASSERT_TRUE(parsedGrouping.empty());
}
