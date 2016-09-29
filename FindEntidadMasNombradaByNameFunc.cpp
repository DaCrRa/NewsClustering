/*
 * FindEntidadMasNombradaByNameFunc.cpp
 *
 *  Created on: 29 de sept. de 2016
 *      Author: dancre
 */

#include "EntidadNombrada.h"

#include <list>
#include <string>
#include <algorithm>

EntidadNombrada findEntidadNombradaByName(std::list<EntidadNombrada> entidades, std::string name) {
    auto it = std::find_if( std::begin(entidades),
                            std::end(entidades),
                            [&](const EntidadNombrada& e){ return e.getEntidadNombrada().compare(name) == 0; } );
    return *it;
}
