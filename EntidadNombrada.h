/*
 * EntidadNombrada.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef ENTIDADNOMBRADA_H_
#define ENTIDADNOMBRADA_H_
#include <string>

class EntidadNombrada {

	int frecuencia;
	std::string entidadNombrada;

public:

	EntidadNombrada();
	EntidadNombrada( std::string n, int f);
	int getFrecuencia() const;
	std::string getEntidadNombrada() const;
	void setFrecuencia(int const f);
	void setEntidadNombrada(std::string const en);
	bool esIgual(const EntidadNombrada& en) const;
	std::string toString() const;

};

inline bool operator==(const EntidadNombrada& lhs, const EntidadNombrada& rhs) {
	return lhs.getEntidadNombrada() == rhs.getEntidadNombrada() &&
		lhs.getFrecuencia() == rhs.getFrecuencia();
}

#endif /* ENTIDADNOMBRADA_H_ */
