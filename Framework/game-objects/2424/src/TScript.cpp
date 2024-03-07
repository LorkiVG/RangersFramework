#include "TScript.h"
#include "TPlayer.h"
#include "TGalaxy.h"
#include "TList.h"

namespace TScriptM
{
    unsigned int GetShipScriptData(TShip* ship, int data_num)
    {
        if (data_num < 0 || data_num > 3) return 0;
        if (ship == Player) return 0;
        TScriptShip* ship_script_obj = ship->script_ship;
        if (!ship_script_obj) return 0;
        return ship_script_obj->data[data_num];
    }
    void SetShipScriptData(TShip* ship, int data_num, unsigned int new_val)
    {
        if (data_num < 0 || data_num > 3) return;
        if (ship == Player) return;
        TScriptShip* ship_script_obj = ship->script_ship;
        if (!ship_script_obj) return;
        ship_script_obj->data[data_num] = new_val;
    }
    int GetScriptGroupBaseState(TScriptGroup* group)
    {
        return group->state;
    }

    bool ShipInScript(TShip* ship)
    {
        if (ship == Player) return true;
        TScriptShip* script_object = ship->script_ship;
        if (script_object) return true;
        return false;
    }
    TScript* GetScriptByName(wchar_t* s_name)
    {
        wstring script_name = L"Script.";
        script_name += s_name;

        TScript* target_script = 0;
        TList* scripts_list = Galaxy->scripts;
        for (int i = 0; i < scripts_list->count; ++i)
        {
            TScript* script = (TScript*)scripts_list->items[i];
            if (wcscmp(script->name, script_name.c_str())) continue;
            target_script = script;
            break;
        }

        return target_script;
    }
    TScriptState* GetScriptStateByName(TScript* script, wstring state_name)
    {
        if (state_name == L"") return 0;

        TScriptState* target_state = 0;
        TList* state_list = script->states;
        for (int i = 0; i < state_list->count; ++i)
        {
            TScriptState* state = (TScriptState*)state_list->items[i];
            if (wcscmp(state->name, state_name.c_str())) continue;
            target_state = state;
            break;
        }

        return target_state;
    }
    TScriptGroup* GetScriptGroupByNum(TScript* script, int group_num)
    {
        return (TScriptGroup*)script->groups->items[group_num];
    }
    TScriptGroup* GetScriptGroupByName(TScript* script, wchar_t* group_name)
    {
        TScriptGroup* target_group = 0;
        TList* groups_list = script->groups;
        for (int i = 0; i < groups_list->count; ++i)
        {
            TScriptGroup* group = (TScriptGroup*)groups_list->items[i];
            if (wcscmp(group->name, group_name)) continue;
            target_group = group;
            break;
        }

        return target_group;
    }
    int GetScriptGroupNum(TScript* script, TScriptGroup* group)
    {
        TScriptGroup* target_group = 0;
        TList* groups_list = script->groups;
        for (int i = 0; i < groups_list->count; ++i)
        {
            TScriptGroup* cur_group = (TScriptGroup*)groups_list->items[i];
            if (cur_group != group) continue;
            return i;
        }
        return -1;
    }
    TScriptState* GetScriptStateByNum(TScript* script, int state_num)
    {
        TList* states_list = script->states;
        return (TScriptState*)states_list->items[state_num];
    }
};