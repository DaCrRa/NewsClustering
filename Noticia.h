/*
 * Noticia.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef NOTICIA_H_
#define NOTICIA_H_
#include "ItemAgrupable.h"

class Noticia : public ItemAgrupable {
private:
	std::string titulo;
	std::string cuerpo;
	std::list<EntidadNombrada> entidades;
	std::list<std::string> entidadesR;

	void setEntidades();
	void agregarEntidad(std::string nombre);

	const double UMBRAL_DE_RELEVANCIA_DE_ENTIDADES = 0.3;
	const double UMBRAL_ENTIDADES_RELEVANTES_EN_NOTICIA_A_AGRUPAR = 0.3;

public:
	Noticia();
	Noticia(std::string titulo, std::string cuerpo, std::string ruta);

	void setTitulo(std::string titulo);
	void setCuerpo(std::string cuerpo);
	void setPalabrasReservadas(std::string ruta);
	void actualizar();

	std::string getTitulo()const;
	std::string getCuerpo()const;
	EntidadNombrada getMasFrecuente()const;
	std::list<EntidadNombrada> getEntidades()const;
	std::list<std::string> getPalabrasReservadas()const;
	std::list<EntidadNombrada> getEntidadesRelevantes()const;
	bool esAgrupablePorEntidadMasNombrada(ItemAgrupable& n) const;
	bool esAgrupablePorTematica(ItemAgrupable& n) const;
	bool entidadMasNombradaEstaEnTituloDe(ItemAgrupable& n) const;
	bool entidadesRelevantesAparecenEn(ItemAgrupable& n) const;
	std::string toString()const;
};

#endif /* NOTICIA_H_ */
