/*
 * NoticiaFolderReader.h
 *
 *  Created on: 27 de sept. de 2016
 *      Author: dancre
 */

#ifndef NOTICIAFOLDERREADER_H_
#define NOTICIAFOLDERREADER_H_

#include <list>
#include <experimental/filesystem>

#include "ItemAgrupable.h"
#include "NoticiaParser.h"

class NoticiaFolderReader {
private:
	std::experimental::filesystem::path folder;
	std::shared_ptr<NoticiaParser> parser;
public:
	NoticiaFolderReader(const std::string& folderName,
			const std::shared_ptr<NoticiaParser> p) :
		folder(folderName),
		parser(p) {}
	std::list<ItemAgrupablePtr> getNoticias();
};
#endif /* NOTICIAFOLDERREADER_H_ */
