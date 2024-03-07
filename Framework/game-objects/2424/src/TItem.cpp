#include "Logger.h"
#include "VMT.h"
#include "TItem.h"

using namespace std;

namespace TItemM
{
    byte ItemType(TItem* item)
    {
        return item->item_type;
    }

    const wchar_t* ItemOwnerString(TItem* item)
    {
        wstring customFaction = TItemM::ItemCustomFaction(item);
        if(customFaction != L"")
        {
            return customFaction.c_str();
        }
        byte owner = item->race;
        switch (owner)
        {
            case Kling:
                if(TEquipmentM::IsEquipment(item))
                {
                    TEquipment* equipment = TEquipmentM::AsEquipment(item);
                    switch(equipment->sub_race)
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
                }
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
            case None:
                return L"None";
            case PirateClan:
                return L"Pirate";
            default:
                return L"Empty";
        }
    }
    wstring ItemCustomFaction(TItem* item)
    {
        byte itemType = item->item_type;
        if(TEquipmentM::IsEquipment(item))
        {
            TEquipment* equipment = TEquipmentM::AsEquipment(item);
            if(equipment->custom_faction != nullptr)
            {
                return equipment->custom_faction;
            }
            else 
            {
                return L"";
            }
           
        }
        else
        {
            return L"";
        }
    }
}

namespace TEquipmentM
{
    TEquipment* AsEquipment(TItem* item)
    {
        return ((TEquipment*)item);
    }
    bool IsEquipment(TItem* item)
    {
        if(TItemM::ItemType(item) > 7)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}