#include "defines.h"
#include "declarations.h"

struct TShipGoodsItem {
    int cnt;
    int cost;
    int _8;
    int _C;
};


struct TGoodsShopItem {
    int count;
    float e_price;
    int sell_price;
    int buy_price;
};

struct TSetItem {
    int a;
    int b;
    word c;
};

struct TDomResearchProgress {
    float progress;
    int material;
};

struct TStorageUnit {
    PTR place;
    _gap_32 _004;
    TItem* item;
    _gap_32 _00C;
    _gap_32 _010;
    _gap_32 _014;
    _gap_32 _018;
    _gap_32 _01C;
};

struct TQuestGameContent {};
struct TTextField {};
struct TQuestParameter {};
struct TArrayRectGR {};
struct TShopSlot {};
struct TStoredItem {};
struct TPlayerHoldUnit {};
struct TJournalRecord {}; // 0x0c

struct TPoint {
    int x;
    int y;
};

struct TPos {
    float x;
    float y;
};

struct TRect {
    int x_1;
    int y_1;
    int x_2;
    int y_2;
};

struct TPos_pair {
    TPos p1;
    TPos p2;
};

struct TGoneItem {
    _pair_byte pos;
    byte terrain_type;
    _gap _3;
    int terrain_needed;
    _gap_32 _8;
    TItem* item;
};

struct TCustomShipInfo {
    STR InfoType;
    STR InfoDescription;

    STR InfoData1;
    STR InfoData2;
    STR InfoData3;

    STR InfoTextData1;
    STR InfoTextData2;
    STR InfoTextData3;

    PTR OnActCode;
    bool IsInit;
    bool Delete;
    _gap _[2];
};