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

	std::list<std::list<std::string> > groups = a1.agruparNoticias();

	int i = 0;
	for (std::list<std::string> grupo : groups) {
		std::cout << "GROUP " << ++i << std::endl;
		for (std::string titulo : grupo) {
			std::cout << "*[" << titulo << "]" << std::endl;
		}
		std::cout << "======" << std::endl;
		std::cout << std::endl;
	}

	return 0;
}
