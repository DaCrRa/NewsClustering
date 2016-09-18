#include <gmock/gmock.h>

#include "NoticiaIf.h"

class NoticiaIfMock : public NoticiaIf {

public:
	MOCK_METHOD1(setTitulo, void(std::string));
	MOCK_METHOD1(setCuerpo, void(std::string));
	MOCK_METHOD1(setPalabrasReservadas, void(std::string));
	MOCK_METHOD0(actualizar, void());

	MOCK_CONST_METHOD0(getTitulo, std::string());
	MOCK_CONST_METHOD0(getCuerpo, std::string());
	MOCK_CONST_METHOD0(getMasFrecuente, EntidadNombrada());
	MOCK_CONST_METHOD0(getEntidades, std::list<EntidadNombrada>());
	MOCK_CONST_METHOD0(getPalabrasReservadas, std::list<std::string>());
	MOCK_CONST_METHOD0(getEntidadesRelevantes, std::list<EntidadNombrada>());
	MOCK_CONST_METHOD1(esAgrupablePorEntidadMasNombrada, bool(NoticiaIf&));
	MOCK_CONST_METHOD1(esAgrupablePorTematica, bool(NoticiaIf&));
	MOCK_CONST_METHOD0(toString, std::string());
};
