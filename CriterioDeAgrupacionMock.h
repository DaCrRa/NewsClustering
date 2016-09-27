#include <gmock/gmock.h>

#include "CriterioDeAgrupacion.h"

class CriterioDeAgrupacionMock : public CriterioDeAgrupacion {

public:
	MOCK_METHOD2(sonAgrupables, bool(ItemAgrupablePtr&, ItemAgrupablePtr&));
};
