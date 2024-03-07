#pragma once
#include "structs.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

struct __cls 
{
    FUNC* methods_p;              ///< указатель на указатель на первый метод в списке методов ( == &methods)
    uint32_t  _04;                    ///< служебные поля, обычно равны нулю, не знаю за что отвечают
    uint32_t  _08;
    uint32_t  _0C;
    uint32_t  _10;
    uint32_t  _14;
    uint32_t  _18;
    uint32_t  _1C;
    char* type_name;              ///< имя класса
    uint32_t  type_size;              ///< размер экземпляра класса
    __cls* parent_class;           ///< указатель на родительский класс ( == 0, если класс примитивный, обычно == VMT_TObject)
    FUNC      safe_call_exception;
    FUNC      after_construction;     ///< исполняется после конструктора
    FUNC      before_destruction;     ///< исполняется перед деструктором
    FUNC      dispatch;               ///< ?
    FUNC      default_handler;        ///< ?
    FUNC      new_instance;           ///< ?
    FUNC      free_instance;          ///< ?

    FUNC      destroy;                ///< деструктор
    FUNC      methods[100];           ///< список методов, у разных классов разное количество методов
};
struct VMT_TScriptShip : __cls {};
typedef __cls* VMT;


struct VMT_TList 
{
    FUNC*     methods;
    uint32_t  _04[7];
    // [0] = void (__fastcall *)(TList *, int, _DWORD
    STR       type_name;
    uint32_t  type_size;
    VMT    parent_class;
    FUNC      safe_call_exception;
    FUNC      after_construction;
    FUNC      before_destruction;
    FUNC      dispatch;
    FUNC      default_handler;
    FUNC      new_instance;
    FUNC      free_instance;

    FUNC      destroy;
    void      (__fastcall *grow)(TList*);
    void      (__fastcall *notify)();
    void      (__fastcall *clear)(TList*);
    void      (__fastcall *error)(TList*, int, int);
};


struct VMT_TEquipmentWithActCode {};

struct VMT_index 
{
    string name;
    VMT vmt;
};

extern std::vector<VMT_index> class_list;

struct VMT_helper 
{
    void* self_ptr;
    void* intf_table;
    void* auto_table;
    void* init_table;
    void* type_info;
    void* field_table;
    void* method_table;
    void* dynamic_table;
    std::uint8_t* class_name;
    uint32_t instance_size;
    VMT parent;
    void* safe_call_exception;
    void* after_construction;
    void* before_destruction;
    void* dispatch;
    void* default_handler;
    void* new_instance;
    void* free_instance;
    void* destroy;
    void* methods[];
};

constexpr int vmt_base_offset = -offsetof(VMT_helper, methods);;

VMT_helper* vmt_struct(VMT vmt);

void* SelfPtr(VMT vmt);
void* IntfTable(VMT vmt);
void* AutoTable(VMT vmt);
void* InitTable(VMT vmt);
void* TypeInfo(VMT vmt);
void* FieldTable(VMT vmt);
void* MethodTable(VMT vmt);
void* DynamicTable(VMT vmt);
void* SafeCallException(VMT vmt);
void* AfterConstruction(VMT vmt);
void* BeforeDestruction(VMT vmt);
void* Dispatch(VMT vmt);
void* DefaultHandler(VMT vmt);
void* NewInstance(VMT vmt);
void* FreeInstance(VMT vmt);
void* Destroy(VMT vmt);
uint32_t InstanceSize(VMT vmt);
VMT   Parent(VMT vmt);
void* Method(VMT vmt, int index);

bool IsSubClass(VMT child, VMT parent);
std::string ClassName(VMT vmt);
VMT get_class(const std::string& name);
void add_class(VMT);


static VMT vmt_TObject = nullptr;
static VMT vmt_TObjectEx = nullptr;
static VMT vmt_TObjectSE = nullptr;
static VMT vmt_TConstellation = nullptr;
static VMT vmt_TStar = nullptr;
static VMT vmt_THole = nullptr; 
static VMT vmt_TPlanet = nullptr;
static VMT vmt_TRanger = nullptr;
static VMT vmt_TShip = nullptr;
static VMT vmt_TNormalShip = nullptr;
static VMT vmt_TPlayer = nullptr;
static VMT vmt_TMissile = nullptr; 
static VMT vmt_TAsteroid = nullptr;
static VMT vmt_TItem = nullptr;
static VMT vmt_TEquipment = nullptr;
static VMT vmt_THull = nullptr;
static VMT vmt_TGoods = nullptr;
static VMT vmt_TScript = nullptr;
static VMT_TScriptShip *vmt_TScriptShip = nullptr;

extern TScriptShip* (__fastcall* TScriptShip_Create) (VMT*, int8_t flag);
extern int(__fastcall* TScriptShip_Destroy) (TScriptShip* list, int8_t flag);

extern TScriptShip* (__fastcall* TScriptShip_New) (VMT*);
extern void* (__fastcall* GetMem) (int);
extern void(__fastcall* FreeMem) (void*);

extern unordered_map<string, VMT> class_name_to_vmt;
extern unordered_set<VMT> vmt_set;