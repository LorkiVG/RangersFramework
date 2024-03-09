#include "TGalaxy.h"
#include "Logger.h"
#include "MathHelper.h"

void MyTGalaxyNextDay(TGalaxy* galaxy)
{
    Logger::WriteChar("VGFramework TGalaxyNextDay CALLED");

    string tstr = "LAST constellation: " + to_string(galaxy->id_constellation);
    Logger::WriteChar(tstr.c_str());
}

namespace TGalaxyM 
{
    int GetGalaxySeed()
    {
        return Galaxy->gen_seed;
    }
    std::uint8_t GalaxyTechLevel()
    {
        return Galaxy->GTL;
    }
    std::uint8_t GalaxyDiffLevels(int diff_num)
    {
        return Galaxy->diff_levels[diff_num];
    }
    
    int DistBetweenCoords(
        int Xa,
        int Ya,
        int Xb,
        int Yb
    )
    {
        int distX = Xa - Xb;
        int distY = Ya - Yb;
        return MathM::BankRound(sqrt(distX * distX + distY * distY));
    }
};