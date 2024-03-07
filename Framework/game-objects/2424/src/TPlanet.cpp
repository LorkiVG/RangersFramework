#include "Logger.h"
#include "TStar.h"
#include "TPlanet.h"

namespace TPlanetM 
{
    const wchar_t* PlanetCustomFaction(TPlanet* planet)
    {
        return planet->custom_faction;
    }
    const wchar_t* PlanetOwnerString(TPlanet* planet)
    {
        byte owner = planet->owner;
        byte race = planet->race;
        byte subOwner = planet->star->series;
        if(TPlanetM::PlanetCustomFaction(planet) != nullptr)
        {
            return TPlanetM::PlanetCustomFaction(planet);
        }
        switch (owner)
        {
            case Kling:
                switch (subOwner)
                {
                    case 0:
                        return L"Blazer";
                    case 1:
                        return L"Keller";
                    case 2:
                        return L"Terron";
                    default:
                        return L"Kling";
                }
                break;
            
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
}