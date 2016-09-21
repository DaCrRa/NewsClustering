
#ifndef NOTICIAIF_H_
#define NOTICIAIF_H_
#include <string>
#include <list>
#include <memory>
#include <exception>

#include "EntidadNombrada.h"

class NoEntidadNombradaException : public std::exception {
public:
	const char* what() const throw() {
		return "No hay entidades nombradas";
	}
};

class NoticiaIf;
typedef std::shared_ptr<NoticiaIf> NoticiaIfPtr;

class NoticiaIf {

public:
	virtual void setTitulo(std::string titulo) = 0;
	virtual void setCuerpo(std::string cuerpo) = 0;
	virtual void setPalabrasReservadas(std::string ruta) = 0;
	virtual void actualizar() = 0;

	virtual std::string getTitulo() const = 0;
	virtual std::string getCuerpo() const = 0;
	virtual EntidadNombrada getMasFrecuente() const = 0;
	virtual std::list<EntidadNombrada> getEntidades() const = 0;
	virtual std::list<std::string> getPalabrasReservadas() const = 0;
	virtual std::list<EntidadNombrada> getEntidadesRelevantes() const = 0;
        virtual bool esAgrupablePorEntidadMasNombrada(NoticiaIf& n) const = 0;
        virtual bool esAgrupablePorTematica(NoticiaIf& n) const = 0;
        virtual bool entidadMasNombradaEstaEnTituloDe(NoticiaIf& n) const = 0;
        virtual bool entidadesRelevantesAparecenEn(NoticiaIf& n) const = 0;
	virtual std::string toString() const = 0;

	virtual ~NoticiaIf() {}
};

#endif /* NOTICIAIF_H_ */
