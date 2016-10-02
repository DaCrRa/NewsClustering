/*
 * GroupingJsonSerializer.h
 *
 *  Created on: 2 Oct 2016
 *      Author: dancre
 */

#ifndef GROUPINGJSONSERIALIZER_H_
#define GROUPINGJSONSERIALIZER_H_

#include <ostream>
#include <list>

#include "ItemAgrupable.h"

class GroupingJsonSerializer {
public:
	void serialize(const std::list<std::list<ItemAgrupablePtr> >& grouping, std::ostream& output);
};

#endif /* GROUPINGJSONSERIALIZER_H_ */
