#include "TStar.h"
#include "TList.h"


namespace TStarM {
    int StarShips(TStar* star)
    {
        return star->ships->count;
    }
    //     
    TShip* StarShips(TStar* star, int index)
    {
        return (TShip*)star->ships->items[index];
    }
};