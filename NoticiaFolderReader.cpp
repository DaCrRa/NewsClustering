/*
 * NoticiaFolderReader.cpp
 *
 *  Created on: 27 de sept. de 2016
 *      Author: dancre
 */

#include "NoticiaFolderReader.h"
#include "NoticiaParser.h"

#include <experimental/filesystem>
#include <fstream>

std::list<ItemAgrupablePtr> NoticiaFolderReader::getNoticias() {
	std::experimental::filesystem::path stopListPath = folder / std::experimental::filesystem::path(STOPLIST_FILENAME);

	std::list<ItemAgrupablePtr> noticias;

	std::experimental::filesystem::path newsSubFolder = folder / std::experimental::filesystem::path(NEWS_SUBFOLDER);

	for(auto& newFile : std::experimental::filesystem::directory_iterator(newsSubFolder)) {
		try {
			std::ifstream filestream(newFile.path());
			NoticiaParser p(filestream, stopListPath);
			noticias.push_back(ItemAgrupablePtr(new Noticia(std::move(p.parse()))));
		} catch (NoticiaInvalidaException& e) {
			// Just try the next one
		}
	}

	return noticias;
}
