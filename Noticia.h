/*
 * Noticia.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef NOTICIA_H_
#define NOTICIA_H_
#include "NoticiaIf.h"

class Noticia : public NoticiaIf {
private:
	std::string titulo;
	std::string cuerpo;
	std::list<EntidadNombrada> entidades;
	std::list<std::string> entidadesR;

	void setEntidades();
	void agregarEntidad(std::string nombre);
	bool esletra(char c) const;

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
	bool esAgrupablePorEntidadMasNombrada(NoticiaIf& n) const;
	bool esAgrupablePorTematica(NoticiaIf& n) const;
	bool entidadMasNombradaEstaEnTituloDe(NoticiaIf& n) const;
	bool entidadesRelevantesAparecenEn(NoticiaIf& n) const;
	std::string toString()const;
};

#endif /* NOTICIA_H_ */
