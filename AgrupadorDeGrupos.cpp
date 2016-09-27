/*
 * AgrupadorDeGrupos.cpp
 *
 *  Created on: 25 de sept. de 2016
 *      Author: dancre
 */

#include "AgrupadorDeGrupos.h"

#include <algorithm>

std::list<std::list<ItemAgrupablePtr> > AgrupadorDeGrupos::agrupar(const std::list<std::list<ItemAgrupablePtr> >& grupos) {
	std::list<std::list<ItemAgrupablePtr> > outputGroups;
	std::list<std::list<ItemAgrupablePtr> > remainingGroups(grupos);

	while (!remainingGroups.empty()) {
		std::list<ItemAgrupablePtr> group(remainingGroups.front());
		remainingGroups.pop_front();
		outputGroups.push_back(group);
		auto& lastOutputGroup = outputGroups.back();
		for (ItemAgrupablePtr item : lastOutputGroup) {
			auto groupableGroupIt = encontrarGrupo(agrupableCon(item), remainingGroups);
			while (groupableGroupIt != remainingGroups.end()) {
				lastOutputGroup.insert(lastOutputGroup.end(),
						groupableGroupIt->begin(),
						groupableGroupIt->end());
				remainingGroups.erase(groupableGroupIt);
				groupableGroupIt = encontrarGrupo(agrupableCon(item), remainingGroups);
			}
		}
		if (lastOutputGroup.empty()) {
			outputGroups.pop_back();
		}
	}
	return outputGroups;
}

std::list<std::list<ItemAgrupablePtr> >::iterator AgrupadorDeGrupos::encontrarGrupo(
			const std::function<bool(ItemAgrupablePtr&)>& criterio,
			std::list<std::list<ItemAgrupablePtr> >& grupos) {

	return std::find_if(
			grupos.begin(),
			grupos.end(),
			[&](std::list<ItemAgrupablePtr>& grupo) -> bool {
				return encontrarItem(criterio, grupo) != grupo.end();
			}
	);
}

std::list<ItemAgrupablePtr>::iterator AgrupadorDeGrupos::encontrarItem(
				const std::function<bool(ItemAgrupablePtr&)>& criterio,
				std::list<ItemAgrupablePtr>& items) {

	return std::find_if(
			items.begin(),
			items.end(),
			criterio);
}

std::function<bool(ItemAgrupablePtr&)> AgrupadorDeGrupos::agrupableCon(ItemAgrupablePtr& item) {
	return [&](ItemAgrupablePtr& item2) -> bool {
		return criterio->sonAgrupables(item, item2);
	};
}
