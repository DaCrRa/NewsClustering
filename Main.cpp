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
#include "NoticiaPlainTextParser.h"
#include "NoticiaJsonParser.h"
#include "TweetParser.h"
#include "AgrupadorDeGrupos.h"
#include "AgrupadorDeItems.h"
#include "PorTematica.h"
#include "PorEntidadMasNombrada.h"
#include "GroupingJsonSerializer.h"

std::list<ItemAgrupablePtr> getPlainTextNoticias(const std::string& folder, const std::string& stopList) {
	NoticiaFolderReader r(
			folder,
			std::shared_ptr<NoticiaParser>(new NoticiaPlainTextParser(stopList))
	);
	return r.getNoticias();
}

std::list<ItemAgrupablePtr> getJsonNoticias(const std::string& folder, const std::string& stopList) {
	NoticiaFolderReader r(
			folder,
			std::shared_ptr<NoticiaParser>(new NoticiaJsonParser(stopList))
	);
	return r.getNoticias();
}

std::list<std::shared_ptr<Tweet> > getTweets(const std::string& file, const std::string& stopList) {
	std::ifstream inputStream(file);
	TweetParser p(inputStream, stopList);
	return p.parse();
}

int main(int argc, const char* argv[]) {
	if (argc == 1) {
		std::cerr << "Dime el path a los datos!" << std::endl;
		return 1;
	}

	try {
		std::experimental::filesystem::path dataPath(argv[1]);
		std::string stopListFile(dataPath / "ES_stopList.txt");

		std::list<ItemAgrupablePtr> items;

		auto noticiasFromPlainTextFiles = getPlainTextNoticias(dataPath / "news", stopListFile);
		items.insert(items.end(), noticiasFromPlainTextFiles.begin(), noticiasFromPlainTextFiles.end());

		auto tweets = getTweets(dataPath / "tuits.txt", stopListFile);
		items.insert(items.end(), tweets.begin(), tweets.end());

		auto noticiasFromJsonFiles = getJsonNoticias(dataPath / "news_json", stopListFile);
		items.insert(items.end(), noticiasFromJsonFiles.begin(), noticiasFromJsonFiles.end());


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

		GroupingJsonSerializer s;
		std::cout << "Guardando agrupacion por entidad mas nombrada en por_entidad.json...";
		std::ofstream porEntidadOut("por_entidad.json");
		s.serialize(agrupadosPorEntidad, porEntidadOut);
		std::cout << "Hecho!" << std::endl;

		std::cout << "Guardando agrupacion por tema en por_tema.json...";
		std::ofstream porTemaOut("por_tema.json");
		s.serialize(agrupadosPorTematica, porTemaOut);
		std::cout << "Hecho!" << std::endl;

	} catch (std::experimental::filesystem::filesystem_error& e) {
		std::cerr << "Error al operar con el sistema de archivos" << std::endl;
		std::cerr << e.what() << std::endl;
		return 2;
	}
	return 0;
}

