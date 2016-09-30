#include <gmock/gmock.h>

#include "ItemAgrupable.h"

class ItemAgrupableMock : public ItemAgrupable {
public:
	MOCK_CONST_METHOD0(getTextoDestacado, std::string());
	MOCK_CONST_METHOD0(getMasFrecuente, EntidadNombrada());
	MOCK_CONST_METHOD0(getEntidades, std::list<EntidadNombrada>());
	MOCK_CONST_METHOD1(esAgrupablePorEntidadMasNombrada, bool(ItemAgrupable&));
	MOCK_CONST_METHOD1(esAgrupablePorTematica, bool(ItemAgrupable&));
	MOCK_CONST_METHOD0(admiteAgrupacionPorCoincidenciaDeCualquierEntidad, bool());
};
