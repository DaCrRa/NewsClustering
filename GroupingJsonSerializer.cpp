/*
 * GroupingJsonSerializer.cpp
 *
 *  Created on: 2 Oct 2016
 *      Author: dancre
 */

#include "GroupingJsonSerializer.h"

#include <json/json.h>

void GroupingJsonSerializer::serialize(const std::list<std::list<ItemAgrupablePtr> >& grouping, std::ostream& output) {
	Json::Value groupsJson;
	int i = 0;
	for (auto& group : grouping) {
		int j = 0;
		for (auto& item : group) {
			groupsJson[i][j++] = item->getTextoDestacado();
		}
		i++;
	}
	output << groupsJson;
}
