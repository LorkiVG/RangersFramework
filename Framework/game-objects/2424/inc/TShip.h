#pragma once
#include <vector>
#include "VMT.h"


namespace TShipM 
{
    const wchar_t* ShipOwnerString(TShip* ship);

    wstring ShipType(TShip* ship);
  
    void ShipType(TShip* ship,wchar_t* type);
    byte ShipTypeN(TShip* ship);
    int32_t ShipMoney(TShip* ship);
    void ShipMoney(TShip* ship, int32_t money);
    byte ShipSubType(TShip* ship);
    wstring ShipCustomFaction(TShip* ship); 
    TStar* ShipStar(TShip* ship);    
    TPlanet* GetShipPlanet(TShip* ship);
    TShip* GetShipRuins(TShip* ship);   
    bool ShipInHyperSpace(TShip* ship);
    bool ShipInNormalSpace(TShip* ship);
    
    
    int ShipCoordX(TShip* ship);
    int ShipCoordY(TShip* ship);
    int DistShips(TShip* ship1, TShip* ship2);
    bool IsSpecialAgent(TShip* ship);
    int ShipSubrace(TShip* ship);
    int ShipSubrace(TShip* ship, int sub_race);
    void ShipJoinScript(TShip* ship, wchar_t* path);
};

struct TShipIliness {
    unkint32 _00;
    unkint32 _04;
    int immunity; 
    unkint32 _B0; //Тоже как-то связано как то с вирусным периодом
    int turn; //Для установки нужно прибавить +308
    
    unkint32 _12;

};

struct TShip {
    VMT cls;

    int id;
    STR name;
    WSTR custom_type_name;
    byte type;
    byte owner;                         ///< Овнер корабля
    empty16 _012;                       
    _pair_float pos;                    ///< Координаты корабля в системе
    TPlanet* cur_planet;                ///< Указатель на планету на которой находится корабль
    TRuins* cur_ship;                   ///< Указатель на корабль(в большиснтве случаев станцию так что помечено как структура станции) в которой корабль сейчас
    TStar* cur_star;                    ///< Указатель на звезду в которой корабль сейчас
    TStar* prev_star;                   ///< Указатель на звезду, из которой корабль прилетел в текущую (если корабль ещё никуда не слетал, то будет записана нулями(но проверено))
    TPlanet* home_planet;               ///< Родная планета спавна корабля
    TShipGoodsItem goods[8];            ///< Массив с данными о товарах
    int capital;                        ///< Капитал
    float capital_coof;                 ///< capital / _064  
    float strength;                     ///< Сила корабля
    float strength_coof;                ///< strength /_06C
    float strength_relative_rangers;    ///< Делит strength / Galaxy->rangers_average_capital

    unkfloat _064;
    _gap _068;
    _gap _069;
    _gap _06A;
    _gap _06B;
    unkfloat _06C;

    _gap _070;
    _gap _071;
    _gap _072;
    _gap _073;

    //Какой-то инт хз короче
    _gap _074;
    _gap _075;
    _gap _076;
    _gap _077;

    unkint8 is_player; // Возможно это маркер на то что игрок ли это
    _gap _079;
    _gap _07A;
    _gap _07B;

    int free_space;
    int gen_seed;
    int rnd_seed;

    int turncreate; //Ход рождения корабля
    int curturn; //Да именно текущий ход, а не кол-во дней с создания

    int money; //Деньги


    _gap _094;
    _gap _095;
    _gap _096;
    _gap _097;

    THull* hull;
    TFuelTanks* fueltanks;
    TEngine* engine;
    TRadar* radar;
    TScaner* scaner;
    TRepairRobot* droid;
    TCargoHook* hook;
    TDefGenerator* defgen;
    TWeapon* weapons[5];
    byte weapon_cnt;
    byte weaponnormal_cnt; 

    byte skills[6];
    TShipIliness iliness[24];

    _gap_32 _314;

    _gap_32 _318;

    _gap_32 _31C;

    _gap _320;
    _gap _321;
    _gap _322;
    _gap _323;

    _gap_32 _324;

    _gap _328;
    _gap _329;
    _gap _32A;
    _gap _32B;

    _gap _32C;
    _gap _32D;
    _gap _32E;
    _gap _32F;

    TList* custom_ship_infos;
    _gap _334;
    _gap _335;
    _gap _336;
    _gap _337;

    _gap _338;
    _gap _339;
    _gap _33A;
    _gap _33B;

    _gap _33C;
    _gap _33D;
    _gap _33E;
    _gap _33F;
    byte ship_tech_level_knowledge;
    _gap _3A1;
    _gap _3A2;
    _gap _3A3;
    int protoplasm;
    int points;
    int free_points;
    _gap _3B0;
    _gap _3B1;
    _gap _3B2;
    _gap _3B3;
    _gap _3B4;
    _gap _3B5;
    _gap _3B6;
    _gap _3B7;
    TList* items;
    TList* arts;
    TList* drop_items;
    TList* _3C4;
    TList* _3C8;
    TScriptShip* script_ship;
    _gap _3D0;
    _gap _3D1;
    _gap _3D2;
    _gap _3D3;
    _gap _3D4;
    _gap _3D5;
    _gap _3D6;
    _gap _3D7;
    TList* _3D8;
    TList* recently_dropped_items;
    _gap _3E0;
    _gap _3E1;
    _gap _3E2;
    _gap _3E3;
    TList* _3E4;
    TList* rewards;
    int _3EC;
    TList* relation_to_rangers;
    TShip* ship_bad;
    TShip* _3F8;
    TShip* partner;
    int contract_days;
    int face;
    byte pilot_race;
    _gap _409;
    _gap _40A;
    _gap _40B;
    _gap _40C;
    _gap _40D;
    _gap _40E;
    _gap _40F;
    _gap _410;
    _gap _411;
    _gap _412;
    _gap _413;
    _gap _414;
    _gap _415;
    _gap _416;
    _gap _417;
    _gap _418;//проверить
    _gap _419;
    _gap _41A;
    _gap _41B;
    _gap _41C;//проверить
    _gap _41D;
    _gap _41E;
    _gap _41F;
    _gap _420;
    _gap _421;
    _gap _422;
    _gap _423;
    _gap _424;
    _gap _425;
    _gap _426;
    _gap _427;
    byte order;
    _gap _429;
    _gap _42A;
    _gap _42B;
    _gap_32 _42C;  // связано с приказом
    TStar* dest_obj;
    _pair_float dest_pos;
    _gap _43C;  // связано с приказом
    _gap _43D;
    _gap _43E;
    _gap _43F;
    _gap _440;
    _gap _441;
    _gap _442;
    _gap _443;
    _gap _444;
    _gap _445;
    _gap _446;
    _gap _447;
    _gap _448;
    _gap _449;
    _gap _44A;
    _gap _44B;
    byte script_order_absolute;
    _gap _44D;
    _gap _44E;
    _gap _44F;
    PTR graph_ship;
    STR skin;  // или строка шкурки, или объект SE
    _gap _458;
    byte in_hyper_space;
    _gap _45A;
    _gap _45B;
    _gap _45C;
    _gap _45D;
    _gap _45E;
    _gap _45F;
    _gap _460;  // destroy=true
    _gap _461;
    _gap _462;
    _gap _463;
    _gap _464;
    _gap _465;
    _gap _466;
    _gap _467;
    _gap _468;
    _gap _469;
    _gap _46A;
    _gap _46B;
    _gap _46C;
    _gap _46D;
    _gap _46E;
    _gap _46F;
    _gap _470;
    _gap _471;
    _gap _472;
    _gap _473;
    _gap _474;
    _gap _475;
    _gap _476;
    _gap _477;
    _gap _478;
    _gap _479;
    _gap _47A;
    _gap _47B;
    _gap _47C;
    _gap _47D;
    _gap _47E;
    _gap _47F;
    _gap _480;
    _gap _481;
    _gap _482;
    _gap _483;
    _gap _484;
    _gap _485;
    _gap _486;
    _gap _487;
    _gap _488;
    _gap _489;
    _gap _48A;
    _gap _48B;
    _gap _48C;
    _gap _48D;
    _gap _48E;
    _gap _48F;
    int money_xored;  // money ^ 0xA4A576AD
    _gap _494;
    _gap _495;
    _gap _496;
    _gap _497;
    bool no_drop;
    bool no_target;
    bool no_talk;
    bool no_scan;
    _gap _49C;
    _gap _49D;
    _gap _49E;
    _gap _49F;
    _gap _4A0;
    _gap _4A1;
    _gap _4A2;
    _gap _4A3;
    TShip* _4A4;
    _gap _4A8;
    _gap _4A9;
    _gap _4AA;
    _gap _4AB;
    _gap _4AC;
    _gap _4AD;
    _gap _4AE;
    _gap _4AF;

    byte cur_standing;
    _gap _4B1;
    _gap _4B2;
    _gap _4B3;

    float _4B4[7];
};

struct TRuins: public TShip {
    TList* equipment_shop;
    _gap _4D4;
    _gap _4D5;
    _gap _4D6;
    _gap _4D7;
    _gap _4D8;
    _gap _4D9;
    _gap _4DA;
    _gap _4DB;
    _gap _4DC;
    _gap _4DD;
    _gap _4DE;
    _gap _4DF;
    _gap _4E0;
    _gap _4E1;
    _gap _4E2;
    _gap _4E3;
    _gap _4E4;
    _gap _4E5;
    _gap _4E6;
    _gap _4E7;
    _gap _4E8;
    _gap _4E9;
    _gap _4EA;
    _gap _4EB;
    _gap _4EC;
    _gap _4ED;
    _gap _4EE;
    _gap _4EF;
    _gap _4F0;
    _gap _4F1;
    _gap _4F2;
    _gap _4F3;
    _gap _4F4;
    _gap _4F5;
    _gap _4F6;
    _gap _4F7;
    _gap _4F8;
    _gap _4F9;
    _gap _4FA;
    _gap _4FB;
    _gap _4FC;
    _gap _4FD;
    _gap _4FE;
    _gap _4FF;
    _gap _500;
    _gap _501;
    _gap _502;
    _gap _503;
    _gap _504;
    _gap _505;
    _gap _506;
    _gap _507;
    _gap _508;
    _gap _509;
    _gap _50A;
    _gap _50B;
    _gap _50C;
    _gap _50D;
    _gap _50E;
    _gap _50F;
    _gap _510;
    _gap _511;
    _gap _512;
    _gap _513;
    _gap _514;
    _gap _515;
    _gap _516;
    _gap _517;
    _gap _518;
    _gap _519;
    _gap _51A;
    _gap _51B;
    _gap _51C;
    _gap _51D;
    _gap _51E;
    _gap _51F;
    _gap _520;
    _gap _521;
    _gap _522;
    _gap _523;
    _gap _524;
    _gap _525;
    _gap _526;
    _gap _527;
    _gap _528;
    _gap _529;
    _gap _52A;
    _gap _52B;
    _gap _52C;
    _gap _52D;
    _gap _52E;
    _gap _52F;
    _gap _530;
    _gap _531;
    _gap _532;
    _gap _533;
    _gap _534;
    _gap _535;
    _gap _536;
    _gap _537;
    _gap _538;
    _gap _539;
    _gap _53A;
    _gap _53B;
    _gap _53C;
    _gap _53D;
    _gap _53E;
    _gap _53F;
    _gap _540;
    _gap _541;
    _gap _542;
    _gap _543;
    _gap _544;
    _gap _545;
    _gap _546;
    _gap _547;
    _gap _548;
    _gap _549;
    _gap _54A;
    _gap _54B;
    _gap _54C;
    _gap _54D;
    _gap _54E;
    _gap _54F;
    _gap _550;
    _gap _551;
    _gap _552;
    _gap _553;
    float _554;
    TStar* dest_star;
    _gap _55C;
    _gap _55D;
    _gap _55E;
    _gap _55F;
    TSatellite* zond;
    byte _564;
    byte _565;
    byte _566;
    byte _567;
};

struct TTranclucator: public TShip {
    float _4D0;
    STR _4D4;
    TShip* proprietor;
    _gap _4DC;
    _gap _4DD;
    _gap _4DE;
    _gap _4DF;
    _gap _4E0;
    _gap _4E1;
    _gap _4E2;
    _gap _4E3;
    _gap _4E4;
    _gap _4E5;
    _gap _4E6;
    _gap _4E7;
    _gap _4E8;
    _gap _4E9;
    _gap _4EA;
    _gap _4EB;
};

struct TKling: public TShip {
    byte sub_type;
    byte sub_race;
    _gap _4D2;
    _gap _4D3;
    int _4D4;
    byte _4D8;
    byte _4D9;
    _gap _4DA;
    _gap _4DB;
};

struct TNormalShip: public TShip {
    TPlanet* _4D0;
    _gap_32 _4D4;
    _gap_32 _4D8;
    _gap_32 _4DC;
    _gap_32 _4E0;
    _gap_32 _4E4;
    _gap_32 _4E8;
    _gap_32 _4EC;
    word _4F0;
    word _4F2;
    word _4F4;
    word _4F6;
    TPlanet* _4F8;
    float _4FC;
    uint16_t rank;  // Возможно имеет значение только на байте _500
    uint16_t ranknext;
    _gap_32 _504;
    _gap_16 _508;
    uint16_t rankpirate;
    _gap_32 _50C;
};

struct TPirate: public TNormalShip {
    byte in_prison;
    _gap _511;
    _gap _512;
    _gap _513;
    byte sub_type;
    _gap _515;
    _gap _516;
    _gap _517;
    _gap_32 _518;
};

struct TWarrior: public TNormalShip {
    byte sub_type;
    _gap _511;
    _gap _512;
    _gap _513;
};

struct TTransport: public TNormalShip {
    byte sub_type;
    _gap _511;
    _gap _512;
    _gap _513;
};

struct TRanger: public TNormalShip {
    _gap_16 _510;
    _gap _512;
    byte status[3];
    _gap _516;
    _gap _517;
    _gap _518;
    _gap _519;
    _gap _51A;
    _gap _51B;
    _gap _51C;
    _gap _51D;
    _gap _51E;
    _gap _51F;
    TList* _520;
    byte in_prison;
    _gap _525;
    _gap _526;
    _gap _527;
    TShip* _528;
    int base_nod_cur;
    int programs[12];
};