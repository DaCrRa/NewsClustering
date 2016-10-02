/*
 * GroupingJsonSerializer.cpp
 *
 *  Created on: 2 Oct 2016
 *      Author: dancre
 */

#include "GroupingJsonSerializer.h"

void GroupingJsonSerializer::serialize(const std::list<std::list<ItemAgrupablePtr> >& grouping, std::ostream& output) {
	output << "[]";
}
