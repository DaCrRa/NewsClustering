
#ifndef ABSTRACT_ITEMAGRUPABLE_H_
#define ABSTRACT_ITEMAGRUPABLE_H_
#include <string>
#include <list>
#include <memory>
#include <exception>

#include "ItemAgrupable.h"

class AbstractItemAgrupable : public ItemAgrupable {
protected:
	std::list<EntidadNombrada> entidades;
	std::list<std::string> entidadesR;
private:
	void setPalabrasReservadas(const std::string& ruta);
	void setEntidades(const std::string& textoAnalizar);
	void agregarEntidad(const std::string& nombre);
public:
	AbstractItemAgrupable(const std::string& textoAnalizar, const std::string& ruta);
	virtual std::string getTextoDestacado() const = 0;
	EntidadNombrada getMasFrecuente() const;
	std::list<EntidadNombrada> getEntidades() const;
	bool esAgrupablePorEntidadMasNombrada(ItemAgrupable& n) const;
	virtual bool esAgrupablePorTematica(ItemAgrupable& n) const = 0;

	virtual ~AbstractItemAgrupable() {}
};

#endif /* ABSTRACT_ITEMAGRUPABLE_H_ */
