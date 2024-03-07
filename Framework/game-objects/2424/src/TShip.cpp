#include "defines.h"
#include "Logger.h"
#include "Strings.h"
#include "TShip.h"
#include "TList.h"
#include "TScript.h"
#include "TPlayer.h"
#include "TObject.h"
#include "TGalaxy.h"

using namespace std;

struct shipNearby
{
public:
    TShip* Ship;
    int Dist;
};

static vector <shipNearby> ShipsNearby;

namespace TShipM 
{
    const wchar_t* ShipOwnerString(TShip* ship)
    {
        wstring customFaction = TShipM::ShipCustomFaction(ship);
        if(customFaction != L"")
        {
            return customFaction.c_str();
        }

        byte owner = ship->owner;
        byte race = ship->pilot_race;
        switch (ship->owner)
        {
            case Kling:
                switch (TShipM::ShipSubrace(ship))
                {
                    case 0:
                        return L"Blazer";
                    case 1:
                        return L"Keller";
                    case 2:
                        return L"Terron";
                    default:
                        return L"Empty";
                }
                return L"Empty";
            case None:
                return L"None";
            case PirateClan:
                switch (race)
                {
                    case Maloc:
                        return L"PirateMaloc";
                    case Peleng:
                        return L"PiratePeleng";
                    case People:
                        return L"PiratePeople";
                    case Fei:
                        return L"PirateFei";
                    case Gaal:
                        return L"PirateGaal";
                    default:
                        return L"Empty";
                }
                return L"Empty";
            default:
                switch (race)
                {
                    case Maloc:
                        return L"Maloc";
                    case Peleng:
                        return L"Peleng";
                    case People:
                        return L"People";
                    case Fei:
                        return L"Fei";
                    case Gaal:
                        return L"Gaal";
                    default:
                        return L"Empty";
                }
                return L"Empty";
        }
    }
    static wstring ShipType(TShip* ship)
    {
        wchar_t* type = ship->custom_type_name;
        if (type) return type;
        else
        {
            switch (ShipTypeN(ship))
            {
            case(t_Kling):
                return L"Kling";
            case(t_Ranger):
                if (IsSpecialAgent(ship)) return L"FemRanger";
                return L"Ranger";
            case(t_Transport):
                switch (ShipSubType(ship))
                {
                case(0):
                    return L"Transport";
                case(1):
                    return L"Liner";
                case(2):
                    return L"Diplomat";
                }
            case(t_Pirate):
                return L"Pirate";
            case(t_Warrior):
                switch (ShipSubType(ship))
                {
                case(0):
                    return L"Warrior";
                case(1):
                    return L"WarriorBig";
                }
            case(t_Tranclucator):
                return L"Tranclucator";
            case(t_RC):
                return L"RC";
            case(t_PB):
                return L"PB";
            case(t_WB):
                return L"WB";
            case(t_SB):
                return L"SB";
            case(t_BK):
                return L"BK";
            case(t_MC):
                return L"MC";
            case(t_CB):
                return L"CB";
            case(t_UB):
                Logger::WriteMessageError(L"ShipType Wrong ruin t_UB ShipType determination.");
                throw;
            }
        }
    }

    void ShipType(TShip* ship,wchar_t* type)
    {
        *ship->custom_type_name = *type;
    }


    byte ShipTypeN(TShip* ship)
    {
        return ship->type;
    }
 
    int32_t ShipMoney(TShip* ship)
    {
        return ship->money;
    }
    void ShipMoney(TShip* ship, int32_t money)
    {
        ship->money = money;
        ship->money_xored = money ^ 0xA4A576AD;
    }  
    byte ShipSubType(TShip* ship)
    {
        switch (TShipM::ShipTypeN(ship))
        {
        case(t_Kling):
            return ((TKling*)ship)->sub_type;
        case(t_Transport):
            return ((TTransport*)ship)->sub_type;
        case(t_Pirate):
            return ((TPirate*)ship)->sub_type;
        case(t_Warrior):
            return ((TWarrior*)ship)->sub_type;
        }
        return 0;
    }
    wstring ShipCustomFaction(TShip* ship)
    {
        
        TScriptShip* script_object = ship->script_ship;
        if (!script_object) return L"";

        wchar_t* faction_str = script_object->custom_faction;
        if (faction_str) return faction_str;
        else return L"";
    }  
    TStar* ShipStar(TShip* ship)
    {
        return ship->cur_star;
    }

    TPlanet* GetShipPlanet(TShip* ship)
    {
        if (ship == Player)
        {
            if (Player->bridge_num) return Player->bridge_cur_planet;
        }
        return ship->cur_planet;
    }
    TShip* GetShipRuins(TShip* ship)
    {
        if (ship == Player)
        {
            if (Player->bridge_num) return Player->bridge_cur_ship;
        }
        return ship->cur_ship;
    }  
    bool ShipInHyperSpace(TShip* ship)
    {
        return ship->in_hyper_space;
    }
    bool ShipInNormalSpace(TShip* ship)
    {
        return (!GetShipPlanet(ship) && !GetShipRuins(ship) && !ShipInHyperSpace(ship));
    }
    
    
    //  X   
    int ShipCoordX(TShip* ship)
    {
        return ship->pos.x;
    }
    //  Y   
    int ShipCoordY(TShip* ship)
    {
        return ship->pos.y;
    }
    //      
    int DistShips(TShip* ship1, TShip* ship2)
    {
        return TGalaxyM::DistBetweenCoords(ShipCoordX(ship1), ShipCoordY(ship1), ShipCoordX(ship2), ShipCoordY(ship2));
    }
    //      
    bool IsSpecialAgent(TShip* ship)
    {
        if (ship == Player) return false;

        TScriptShip* ship_script_object = ship->script_ship;
        if (!ship_script_object) return false;

        TScript* script = ship_script_object->script;
        if (wcscmp(script->name, L"Script.PC_fem_rangers")) return false;

        TScriptGroup* group = (TScriptGroup*)script->groups->items[ship_script_object->group];
        if (wcscmp(group->name, L"GroupFem")) return false;

        return true;
    }
    int ShipSubrace(
        TShip* ship
    )
    {
        if (TShipM::ShipTypeN(ship) != t_Kling)
        {
            return -1;
        }
        return ((TKling*)ship)->sub_race;
    }
    int ShipSubrace(
        TShip* ship,
        int sub_race
    )
    {
        if (TShipM::ShipTypeN(ship) != t_Kling)
        {
            return -1;
        }
        if (sub_race <= -1) return ((TKling*)ship)->sub_race;
        int old_sub_race = ((TKling*)ship)->sub_race;
        ((TKling*)ship)->sub_race = sub_race;
        return old_sub_race;
    }
    void ShipJoinScript(
        TShip* ship,
        wchar_t* path
    )
    {
        if (ship == Player) return;
        int obj_type = TObjectM::ObjectType(ship);
        if (obj_type != t_ObjShip && obj_type != t_ObjStation)
        {
            Logger::WriteMessageError(L"ShipJoinToScript function error. First argument is not a ship or station.");
            throw;
        }

        wchar_t sep[] = L".";

        TScript* script = TScriptM::GetScriptByName(_wcsdup(Strings::GetParSepStr(path, sep, 0)));
        if (!script)
        {
            Logger::WriteMessageWarning(L"ShipJoinToScript cannot find script by it's name. Path is: " + *path);
            return;
        }

        TScriptGroup* group = TScriptM::GetScriptGroupByName(script, _wcsdup(Strings::GetParSepStr(path, sep, 1)));
        if (!group)
        {
            Logger::WriteMessageWarning(L"ShipJoinToScript cannot find script group by it's name. Path is: " + *path);
            return;
        }

        TScriptState* state;
        wstring state_name = Strings::GetParSepStr(path, sep, 2);
        if (state_name != L"")
        {
            state = TScriptM::GetScriptStateByName(script, state_name);
            if (!state)
            {       
                state = TScriptM::GetScriptStateByNum(script, TScriptM::GetScriptGroupBaseState(group));
                Logger::WriteMessageWarning(L"ShipJoinToScript cannot find script state by it's name. Ship will be added in base group state. Path is: " + *path);
            }
        }      
        else state = TScriptM::GetScriptStateByNum(script, TScriptM::GetScriptGroupBaseState(group));

        TScriptShip* ship_script_obj = ship->script_ship;  
        TScript* old_script = 0;
        if (ship_script_obj)
        {
            old_script = ship_script_obj->script;
            if (script != old_script)
            {
                TList* ship_script_objs_list = old_script->ships;
                for (int i = 0; i < ship_script_objs_list->count; ++i)
                {
                    TScriptShip* cur_obj = (TScriptShip*)ship_script_objs_list->items[i];
                    if (cur_obj == ship_script_obj)
                    {
                        TListM::Delete(ship_script_objs_list, i);
                        break;
                    }
      
                    if (i == ship_script_objs_list->count - 1)
                    {
                        Logger::WriteMessageWarning(L"ShipJoinToScript Can't find ship script object in it's script. Path is: " + *path);
                        return;
                    }
                }
            }
            else
            { 
                if (group == TScriptM::GetScriptGroupByNum(script, ship_script_obj->group) && state == ship_script_obj->state)
                {
                    Logger::WriteMessageWarning(L"ShipJoinToScript This ship is already in target script group and target script state. Path is: " + *path);
                    return;
                }
            }

            if (group != TScriptM::GetScriptGroupByNum(script, ship_script_obj->group))
            {
                for (int i = 0; i <= 3; ++i) TScriptM::SetShipScriptData(ship, i, 0);
                ship_script_obj->custom_faction = 0;
                ship_script_obj->end_order = 0;
                ship_script_obj->hit = 0;
                ship_script_obj->hit_player = 0;
            }
        }
        else
        {
            int sz = *(int*)(int(vmt_TScriptShip) - 40);
            ship_script_obj = (TScriptShip*)GetMem(sz);
            *(VMT_TScriptShip**)ship_script_obj = vmt_TScriptShip;
            for (int i = 4; i < sz; ++i) ((char*)ship_script_obj)[i] = 0;
            ship_script_obj->ship = ship;
        }

        if (script != old_script) TListM::Add(script->ships, ship_script_obj);
        ship_script_obj->script = script;
        ship_script_obj->group = TScriptM::GetScriptGroupNum(script, group);
        ship_script_obj->state = state;
        ship->script_ship = ship_script_obj;
    }
};