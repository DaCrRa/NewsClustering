/*
 * Main.cpp
 *
 *  Created on: 27-dic-2012
 *      Author: Alvaro
 */

#include <iostream>
#include <iterator>
#include <fstream>

#include <experimental/filesystem>

#include "NoticiaFolderReader.h"
#include "TweetParser.h"
#include "AgrupadorDeGrupos.h"
#include "AgrupadorDeItems.h"
#include "PorTematica.h"
#include "PorEntidadMasNombrada.h"

int main(int argc, const char* argv[]) {
	if (argc == 1) {
		std::cerr << "Dime el path a las noticias!" << std::endl;
		return 1;
	}

	std::experimental::filesystem::path dataPath(argv[1]);

	NoticiaFolderReader reader(dataPath);
	std::list<ItemAgrupablePtr> items;
	try {
		items = reader.getNoticias();
	} catch (std::experimental::filesystem::filesystem_error& e) {
		std::cerr << "No puedo abrir el directorio con las noticias!" << std::endl;
		std::cerr << e.what() << std::endl;
		return 3;
	}

	if (items.empty()) {
		std::cerr << "No hay noticias!" << std::endl;
		return 2;
	}

	std::ifstream tweetInputStream(dataPath / "tuits.txt");
	TweetParser tweetParser(tweetInputStream, dataPath / "ES_stopList.txt");
	auto parsedTweets = tweetParser.parse();
	items.insert(items.end(), parsedTweets.begin(), parsedTweets.end());

	AgrupadorDeItems agrupador(CriterioDeAgrupacionPtr(new PorEntidadMasNombrada()));

	std::list<std::list<ItemAgrupablePtr> > agrupadosPorEntidad = agrupador.agrupar(items);

	std::cout << "POR ENTIDAD MAS NOMBRADA:" << std::endl;
	std::cout << std::endl;
	for (std::list<ItemAgrupablePtr> grupo : agrupadosPorEntidad) {
		std::cout << grupo.front()->getMasFrecuente().getEntidadNombrada() << std::endl;
		for (ItemAgrupablePtr item : grupo) {
			std::cout << "*[" << item->getTextoDestacado() << "]" << std::endl;
		}
		std::cout << "======" << std::endl;
		std::cout << std::endl;
	}

	AgrupadorDeGrupos agrupador2(CriterioDeAgrupacionPtr(new PorTematica()));
	std::list<std::list<ItemAgrupablePtr> > agrupadosPorTematica = agrupador2.agrupar(agrupadosPorEntidad);

	std::cout << "POR TEMA:" << std::endl;
	std::cout << std::endl;
	for (std::list<ItemAgrupablePtr> grupo : agrupadosPorTematica) {
		for (ItemAgrupablePtr item : grupo) {
			std::cout << "*[" << item->getTextoDestacado() << "]" << std::endl;
		}
		std::cout << "======" << std::endl;
		std::cout << std::endl;
	}

	return 0;
}
