/*
 * Main.cpp
 *
 *  Created on: 27-dic-2012
 *      Author: Alvaro
 */

#include "iostream"
#include "EntidadNombrada.h"
#include "cstdio"
#include "Noticia.h"
#include "Analizador.h"
#include <iterator>

int main() {

	Analizador a1("data");

	std::list<std::list<NoticiaIfPtr> > groups = a1.agruparNoticiasPorEntidadMasFrecuente();

	std::cout << "POR ENTIDAD MAS NOMBRADA:" << std::endl;
	std::cout << std::endl;
	for (std::list<NoticiaIfPtr> grupo : groups) {
		std::cout << grupo.front()->getMasFrecuente().getEntidadNombrada() << std::endl;
		for (NoticiaIfPtr noticia : grupo) {
			std::cout << "*[" << noticia->getTitulo() << "]" << std::endl;
		}
		std::cout << "======" << std::endl;
		std::cout << std::endl;
	}

	groups = a1.agruparNoticiasPorTematica(groups);

        std::cout << "POR TEMA:" << std::endl;
        std::cout << std::endl;
        for (std::list<NoticiaIfPtr> grupo : groups) {
                for (NoticiaIfPtr noticia : grupo) {
                        std::cout << "*[" << noticia->getTitulo() << "]" << std::endl;
                }
                std::cout << "======" << std::endl;
                std::cout << std::endl;
        }

	return 0;
}
