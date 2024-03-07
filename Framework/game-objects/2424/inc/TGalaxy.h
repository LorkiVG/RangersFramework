#pragma once
#include "VMT.h"

using namespace std;

extern "C" void MyTGalaxyNextDayAsm();

extern "C" void MyTGalaxyNextDay(TGalaxy* galaxy);

namespace TGalaxyM {
    int GetGalaxySeed();
    std::uint8_t GalaxyTechLevel();
    std::uint8_t GalaxyDiffLevels(int diff_num);
    int DistBetweenCoords(int Xa, int Ya, int Xb, int Yb);
};


static TGalaxy* Galaxy = nullptr;

struct TGalaxyEvent {
    VMT cls;

    int type;
    int turn;
    TList* data_list;
    TList* text_list;
};


/** @file */
struct TGalaxy {
    VMT cls;

    //Фактически являются счётчиками--
    uint32_t id_constellation;          ///< ID+1 последнего созданного сектора
    uint32_t id_system;                 ///< ID+1 последнего созданного системы
    uint32_t id_hole;                   ///< ID+1 последней созданой чёрной дыры
    uint32_t id_planet;                 ///< ID+1 последней созданой планеты
    unkuint32 _014;
    unkuint32 _018;
    uint32_t id_ship;                   ///< ID+1 последнего созданного корабля 
    uint32_t id_item;                   ///< ID+1 последнего созданного итема
    uint32_t id_missile;                ///< ID+1 последней созданной ракеты
    //--

    int player_index;                   ///< номер игрока в списке рейнджеров
    TList* stars;                       ///< список звезд
    TList* holes;                       ///< список черных дыр
    TList* unklist;                     ///< список на 4 указателя который ведут на оборудование портреты товары(но пока не разобрано)
    TList* planets;                     ///< список планет
    TList* rangers;                     ///< список рейнджеров

    int pirate_cnt;                     ///< кол-во пиратов
    int pirate_cnt_in_clan;             ///< кол-во пиратов клановых
    int transport_cnt;                  ///< кол-во мирных кораблей в галактике
    int turn;                           ///< текущий ход

    std::uint8_t diff_levels[8];             ///< сложности партии
    int gen_seed;                       ///< сид генерации галактики
    int rnd_seed;                       ///< сид рандома
    int rangers_average_capital;        ///< средний капитал рейнджеров
    int _064;
    float rangers_average_strength;     ///< средняя сила рейнджеров
    int _06C;
    _gap_32 _070;
    _gap_32 _074;
    int eminent_rangers[3];             ///< три самых лучших рейнджера?
    _gap_32 _084;
    _gap_32 _088;
    _gap_32 _08C;
    _gap_32 _090;
    _gap_32 _094;
    _gap_32 _098;
    _gap_32 _09C;
    _gap_32 _0A0;
    _gap_32 _0A4;
    _gap_32 _0A8;
    _gap_32 _0AC;
    _gap_32 _0B0;
    _gap_32 _0B4;
    _gap_32 _0B8;
    _gap_32 _0BC;
    TList* planet_news;                 ///< список новостей
    TList* custom_weapon_infos;
    TStar* keller_attack_star;          ///< цель атаки Келлера
    TList* _0C0;
    TList* _0C4;
    TDomResearchProgress dom_researches[3]; ///< прогресс исследований доминаторских программ
    float _0EC;  // 0.01
    uint8_t GTL;                           ///< ГТУ
    _gap _0F1;
    _gap _0F2;
    _gap _0F3;
    int _0F8;
    int klings_delta_win;
    int pirates_delta_win;
    // +0x100
    int normals_delta_win;
    int _104;
    int _108;
    int _10C;
    int _110;
    int terron_weapon_lock_turn;        ///< ход
    int terron_grow_lock_turn;          ///< ход
    int terron_landing_lock_turn;       ///< ход
    int terron_to_star;                 ///< ход
    int keller_leave;                   ///< ход
    int keller_new_research;            ///< ход
    int blazer_landing;                 ///< ход
    int blazer_self_destruction;        ///< ход
    int terron_turn_win;                ///< ход
    int keller_turn_win;                ///< ход
    int blazer_turn_win;                ///< ход
    int pirate_win_turn;                ///< ход
    int pirate_win_type;                ///< ход
    int coalition_defeated_turn;        ///< ход
    _gap_32 _14C;
    TList* scripts;                     ///< список всех скриптов (в том числе и неактивных?)
    TList* _154;
    TList* _158;
    TList* _15C;
    int gencons;                        /// количество секторов при генерации галактики(по факту оно и нафиг не надо так как выше есть ещё одна переменная но которая хранит именно ID начиная с 0)
    TList* constellations;              ///< список секторов
    _gap_32 _168;
    PTR _16C;                           /// указатель на массив элементов размером 0x60
    _gap_32 _170;
    _gap_32 _174;
    _gap_32 _178;
    bool iron_will;                     ///< флаг железной воли
    _gap _17D;
    bool technic;                       ///< флаг от чита `TECHNIC`
    _gap _17F;
    _gap _180;
    bool ultrascan;                     ///< флаг от чита `ULTRASCAN`
    bool zawarudo;                      ///< флаг от чита `ZAWARUDO`
    bool dump;                          ///< нужен для создания дампа вместе с сейвом?
    STR finalization_name;

    // Тонкие настройки:
    bool AA_enabled;                    ///< флаг тонких настроек
    byte AA_kling_strength;
    byte AA_kling_aggro;
    byte AA_kling_spawn;
    byte AA_pirate_aggro;
    byte AA_coal_aggro;
    byte AA_asteroid_mod;
    byte AA_sun_damage_mod;
    byte AA_extra_inventions;
    byte AA_akrin_mod;
    byte AA_node_drop_mod;
    byte AA_AB_drop_value_mod;
    byte AA_drop_value_mod;
    byte AA_ag_planets;
    byte AA_mi_planets;
    byte AA_in_planets;
    byte AA_extra_rangers;
    byte AA_AB_hitpoints_mod;
    byte AA_AB_damage_mod;
    bool AA_AI_tolerate_junk;
    bool AA_rnd_chaotic;
    bool AA_eq_knowledge_restricted;
    bool AA_ruins_near_stars;
    bool AA_ruins_targetting_full;
    bool AA_special_ships_in_game;
    bool AA_zero_start_exp;
    bool AA_AB_battle_royale;
    bool AA_kling_racial_weapons;
    bool AA_start_center;
    bool AA_max_range_missiles;
    bool AA_old_hyper;
    bool AA_pirate_nodes;
    bool AA_AI_use_shops;
    bool AA_ruins_use_shops;
    bool AA_duplicate_arts;
    byte AA_hull_growth;

    _gap_32 _1AC;
    TList* events;                      ///< список галактических событий
    TList* interface_state_overrides;   ///< список оверрайдов состояния
    TList* interface_text_overrides;    ///< список оверрайдов текста
    TList* interface_image_overrides;   ///< список оверрайдов изображения
    TList* interface_pos_overrides;     ///< список оверрайдов позиции
    TList* interface_size_overrides;    ///< список оверрайдов размера
    _gap_32 _1C8;
    _gap_32 _1CC;  // CRC
    byte _1D0;
    _gap _1D1;
    _gap _1D2;
    _gap _1D3;
};