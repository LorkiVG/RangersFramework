#pragma once
#include "shlobj.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
#define M_PI 3.14159265358979323846

#define t_ObjNone 0
#define t_ObjStar 1
#define t_ObjHole 2
#define t_ObjPlanet 3
#define t_ObjStation 4
#define t_ObjShip 5
#define t_ObjItem 6
#define t_ObjMissile 7
#define t_ObjAsteroid 8
#define t_ObjSector 9

#define Maloc 0
#define Peleng 1
#define People 2
#define Fei 3
#define Gaal 4
#define Kling 5
#define None 6
#define PirateClan 7

#define t_Kling 0
#define t_Ranger 1
#define t_Transport 2
#define t_Pirate 3
#define t_Warrior 4
#define t_Tranclucator 5
#define t_RC 6
#define t_PB 7
#define t_WB 8
#define t_SB 9
#define t_BK 10
#define t_MC 11
#define t_CB 12
#define t_UB 13

#define t_Food 0
#define t_Medicine 1
#define t_Technics 2
#define t_Luxury 3
#define t_Minerals 4
#define t_Alcohol 5
#define t_Arms 6
#define t_Narcotics 7
#define t_Artefact 8
#define t_Artefact2 9
#define t_ArtefactHull 10
#define t_ArtefactFuel 11
#define t_ArtefactSpeed 12
#define t_ArtefactPower 13
#define t_ArtefactRadar 14
#define t_ArtefactScaner 15
#define t_ArtefactDroid 16
#define t_ArtefactNano 17
#define t_ArtefactHook 18
#define t_ArtefactDef 19
#define t_ArtefactAnalyzer 20
#define t_ArtefactMiniExpl 21
#define t_ArtefactAntigrav 22
#define t_ArtefactTransmitter 23
#define t_ArtefactBomb 24
#define t_ArtefactTranclucator 25
#define t_ArtDefToEnergy 26
#define t_ArtEnergyPulse 27
#define t_ArtEnergyDef 28
#define t_ArtSplinter 29
#define t_ArtDecelerate 30
#define t_ArtMissileDef 31
#define t_ArtForsage 32
#define t_ArtWeaponToSpeed 33
#define t_ArtGiperJump 34
#define t_ArtBlackHole 35
#define t_ArtDefToArms1 36
#define t_ArtDefToArms2 37
#define t_ArtArtefactor 38
#define t_ArtBio 39
#define t_ArtPDTurret 40
#define t_ArtFastRacks 41
#define t_Hull 42
#define t_FuelTanks 43
#define t_Engine 44
#define t_Radar 45
#define t_Scaner 46
#define t_RepairRobot 47
#define t_CargoHook 48
#define t_DefGenerator 49
#define t_Weapon1 50
#define t_Weapon2 51
#define t_Weapon3 52
#define t_Weapon4 53
#define t_Weapon5 54
#define t_Weapon6 55
#define t_Weapon7 56
#define t_Weapon8 57
#define t_Weapon9 58
#define t_Weapon10 59
#define t_Weapon11 60
#define t_Weapon12 61
#define t_Weapon13 62
#define t_Weapon14 63
#define t_Weapon15 64
#define t_Weapon16 65
#define t_Weapon17 66
#define t_Weapon18 67
#define t_CustomWeapon 68
#define t_Protoplasm 69
#define t_UselessItem 70
#define t_MicroModule 71
#define t_Cistern 72
#define t_Satellite 73
#define t_UselessCountableItem 74

#define AutoBattleOrder -1
#define NoneOrder 0
#define MoveOrder 1
#define LandingOrder 2
#define JumpOrder 3
#define JumpHoleOrder 4
#define TakeOffOrder 5
#define FollowOrder 6
#define TeleportOrder 7


#define SET_EXPR(lhs, expr)                   *(uint32_t*)&lhs = (uint32_t)(expr);
#define SET_VAR(lhs, rhs)                     *(int8_t**)&lhs = (int8_t*)rhs;
#define SET_VAR_WITH_OFFSET(lhs, rhs, offset) *(int8_t**)&lhs = (int8_t*)rhs + (offset);

struct _pair_byte;
struct _pair_int;
struct _pair_float;
struct _pair_double;

struct TList;
struct TObjectList;



struct THashEC;
struct TCodeEC;
struct TBufEC;
struct TFileEC;
struct TBlockParEC;
struct TBlockParElEC;
struct TDataElEC;
struct TDataEC;
struct TPackFileEC;
struct TPackCollectionEC;
struct TBlockMemUnitEC;
struct TBlockMemEC;
struct TStringsElEC;
struct TStringsEC;
// enum TVarEC_type;
struct TVarEC;
struct TVarArrayEC;
struct TCodeAnalyzerUnitEC;
struct TCodeAnalyzerEC;
struct TExpressionEC;
struct TExpressionInstrEC;
struct TExpressionVarEC;

struct TPlanetTempl;
struct TStarDist;
struct TShipGoodsItem;
struct TGoodsShopItem;
struct TGoneItem;
struct TDomResearchProgress;
struct TGalaxyEvent;
struct TSetItem;
struct TMessagePlayer;
struct TStorageUnit;
struct TQuestGameContent;
struct TTextField;
struct TQuestParameter;
struct TArrayRectGR;
struct TShopSlot;
struct TStoredItem;
struct TPlayerHoldUnit;
struct TJournalRecord;
struct TPlanetNews;

struct TCCInterface;
struct TCBufEC;
struct TCBufControlEC;
struct TCCInterface_El;

struct TThreadEC;
struct TSaver;

struct TBonus;
struct TBonusSpecial;

struct TScript;
struct TScriptShip;
struct TScriptPlace;
struct TScriptItem;
struct TScriptState;
struct TScriptGroup;
struct TScriptStar;
struct TScriptConstellation;
struct TScriptDialog;
struct TScriptDialogMsg;
struct TScriptDialogAnswer;

struct TObjectSE;

struct TMissile;
struct TCustomMissile;
struct TAsteroid;
struct TGalaxy;
struct TStar;
struct TPlanet;
struct THole;
struct TConstellation;


struct TItem;
struct TGoods;
struct TEquipment;
struct THull;
struct TFuelTanks;
struct TEngine;
struct TRadar;
struct TScaner;
struct TRepairRobot;
struct TCargoHook;
struct TDefGenerator;
struct TWeapon;
struct TCountableItem;
struct TEquipmentWithActCode;
struct TCistern;
struct TSatellite;
struct TTreasureMap;
struct TMicromodule;
struct TArtefact;
struct TUselessItem;
struct TProtoplasm;
struct TArtefactTransmitter;
struct TArtefactTranclucator;
struct TArtefactCustom;
struct TCustomWeapon;

struct TShipIliness;
struct TShip;
struct TRuins;
struct TTranclucator;
struct TKling;
struct TNormalShip;
struct TPirate;
struct TWarrior;
struct TTransport;
struct TRanger;
struct TPlayer;