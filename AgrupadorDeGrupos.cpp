/*
 * AgrupadorDeGrupos.cpp
 *
 *  Created on: 25 de sept. de 2016
 *      Author: dancre
 */

#include "AgrupadorDeGrupos.h"

#include <algorithm>

std::list<std::list<NoticiaIfPtr> > AgrupadorDeGrupos::agrupar(const std::list<std::list<NoticiaIfPtr> >& grupos) {
	std::list<std::list<NoticiaIfPtr> > outputGroups;
	std::list<std::list<NoticiaIfPtr> > remainingGroups(grupos);

	while (!remainingGroups.empty()) {
		std::list<NoticiaIfPtr> group(remainingGroups.front());
		remainingGroups.pop_front();
		outputGroups.push_back(group);
		auto& lastOutputGroup = outputGroups.back();
		for (NoticiaIfPtr item : lastOutputGroup) {
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

std::list<std::list<NoticiaIfPtr> >::iterator AgrupadorDeGrupos::encontrarGrupo(
			const std::function<bool(NoticiaIfPtr&)>& criterio,
			std::list<std::list<NoticiaIfPtr> >& grupos) {

	return std::find_if(
			grupos.begin(),
			grupos.end(),
			[&](std::list<NoticiaIfPtr>& grupo) -> bool {
				return encontrarItem(criterio, grupo) != grupo.end();
			}
	);
}

std::list<NoticiaIfPtr>::iterator AgrupadorDeGrupos::encontrarItem(
				const std::function<bool(NoticiaIfPtr&)>& criterio,
				std::list<NoticiaIfPtr>& items) {

	return std::find_if(
			items.begin(),
			items.end(),
			criterio);
}

std::function<bool(NoticiaIfPtr&)> AgrupadorDeGrupos::agrupableCon(NoticiaIfPtr& item) {
	return [&](NoticiaIfPtr& item2) -> bool {
		return criterio->sonAgrupables(item, item2);
	};
}
