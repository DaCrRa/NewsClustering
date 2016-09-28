/*
 * Noticia.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef NOTICIA_H_
#define NOTICIA_H_
#include "AbstractItemAgrupable.h"

class Noticia : public AbstractItemAgrupable {
private:
	std::string titulo;
	std::string cuerpo;

	const double UMBRAL_DE_RELEVANCIA_DE_ENTIDADES = 0.3;
	const double UMBRAL_ENTIDADES_RELEVANTES_EN_NOTICIA_A_AGRUPAR = 0.3;

public:
	Noticia();
	Noticia(const std::string& titulo, const std::string& cuerpo, const std::string& ruta);

	void setTitulo(std::string titulo);
	void setCuerpo(std::string cuerpo);

	std::string getTitulo()const;
	std::string getCuerpo()const;
	std::string getTextoDestacado() const;
	std::list<std::string> getPalabrasReservadas()const;
	std::list<EntidadNombrada> getEntidadesRelevantes()const;
	bool esAgrupablePorEntidadMasNombrada(ItemAgrupable& n) const;
	bool esAgrupablePorTematica(ItemAgrupable& n) const;
	bool entidadMasNombradaEstaEnDestacadoDe(ItemAgrupable& n) const;
	bool entidadesRelevantesAparecenEn(ItemAgrupable& n) const;
	std::string toString()const;
};

#endif /* NOTICIA_H_ */
