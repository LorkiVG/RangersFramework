#pragma once
#include "VMT.h"

namespace TObjectM {
    byte ShipTypeN(TShip* ship);
    int ObjectType(void* obj);
};

struct TObject {
    VMT cls;
};