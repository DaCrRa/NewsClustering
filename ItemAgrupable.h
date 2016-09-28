
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
	virtual std::string getTextoDestacado() const = 0;
	virtual EntidadNombrada getMasFrecuente() const = 0;
	virtual std::list<EntidadNombrada> getEntidades() const = 0;
	virtual bool esAgrupablePorEntidadMasNombrada(ItemAgrupable& n) const = 0;
	virtual bool esAgrupablePorTematica(ItemAgrupable& n) const = 0;

	virtual ~ItemAgrupable() {}
};

#endif /* ITEMAGRUPABLE_H_ */
