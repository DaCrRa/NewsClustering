/*
 * NoticiaFolderReader.cpp
 *
 *  Created on: 27 de sept. de 2016
 *      Author: dancre
 */

#include "NoticiaFolderReader.h"

#include <experimental/filesystem>
#include <fstream>

std::list<ItemAgrupablePtr> NoticiaFolderReader::getNoticias() {

	std::list<ItemAgrupablePtr> noticias;

	for(auto& newFile : std::experimental::filesystem::directory_iterator(folder)) {
		try {
			std::ifstream filestream(newFile.path());
			noticias.push_back(ItemAgrupablePtr(new Noticia(std::move(parser->parse(filestream)))));
		} catch (...) {
			// Just try the next one
		}
	}

	return noticias;
}
