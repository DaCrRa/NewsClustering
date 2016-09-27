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

class NoticiaFolderReader {
private:
	std::experimental::filesystem::path folder;
	static const std::string STOPLIST_FILENAME;
	static const std::string NEWS_SUBFOLDER;
public:
	NoticiaFolderReader(const std::string& folderName) :
		folder(folderName) {}
	std::list<ItemAgrupablePtr> getNoticias();
};
const std::string NoticiaFolderReader::STOPLIST_FILENAME = "ES_stopList.txt";
const std::string NoticiaFolderReader::NEWS_SUBFOLDER = "news";
#endif /* NOTICIAFOLDERREADER_H_ */
