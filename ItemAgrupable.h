
#ifndef ITEMAGRUPABLE_H_
#define ITEMAGRUPABLE_H_
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

class ItemAgrupable;
typedef std::shared_ptr<ItemAgrupable> ItemAgrupablePtr;

class ItemAgrupable {

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
	virtual bool esAgrupablePorEntidadMasNombrada(ItemAgrupable& n) const = 0;
	virtual bool esAgrupablePorTematica(ItemAgrupable& n) const = 0;
	virtual bool entidadMasNombradaEstaEnTituloDe(ItemAgrupable& n) const = 0;
	virtual bool entidadesRelevantesAparecenEn(ItemAgrupable& n) const = 0;
	virtual std::string toString() const = 0;

	virtual ~ItemAgrupable() {}
};

#endif /* ITEMAGRUPABLE_H_ */
