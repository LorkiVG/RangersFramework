#include "Logger.h"
#include "TObject.h"
#include "TShip.h"
#include "TItem.h"
#include "TPlanet.h"


using namespace std;

namespace TObjectM {
    byte ShipTypeN(TShip* ship)
    {
        return ship->type;
    }
    int ObjectType(void* obj)
    {
        VMT vmt = ((TShip*)obj)->cls;
        VMT prev_parent = vmt;
        VMT parent = vmt_struct(vmt)->parent;
        while (parent != vmt_TObjectEx && parent != vmt_TObject) 
        {
            prev_parent = parent;
            parent = ((VMT_helper*)parent)->parent;
        }
        vmt = prev_parent;

        if (vmt == vmt_TShip)
        {
            if (((TShip*)obj)->type < t_RC) return t_ObjShip;
            else return t_ObjStation;
        }
        else if (vmt == vmt_TItem) return t_ObjItem;
        else if (vmt == vmt_TPlanet) return t_ObjPlanet;
        else if (vmt == vmt_TStar) return t_ObjStar;
        else if (vmt == vmt_TAsteroid) return t_ObjAsteroid;
        else if (vmt == vmt_TConstellation) return t_ObjSector;
        else return t_ObjNone;
    }
    
    const wchar_t* ObjectOwnerString(void* obj)
    {
        int objType = TObjectM::ObjectType(obj);
        wstring customFaction;
        
        byte owner;
        byte type;
        byte race;

        TShip* ship;
        TItem* item;
        TPlanet* planet;
        switch (objType)
        {
            case t_ObjShip:
                ship = ((TShip*)obj);
                return TShipM::ShipOwnerString(ship);
            case t_ObjItem:
                item = ((TItem*)obj);
                return TItemM::ItemOwnerString(item);
            case t_ObjPlanet:
                planet = ((TPlanet*)obj);
                return TPlanetM::PlanetOwnerString(planet);
            default:
                Logger::WriteMessageError(L"Object haven't owner param");

                return L"Empty";
        }
        return L"None";
    }
};