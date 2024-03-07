#pragma once
#include "VMT.h"



struct TList {
    VMT_TList* cls;

    uint32_t* items;   ///< указатель на массив
    int count;         ///< количество элементов
    int capacity;      ///< размер выделенной памяти (в элементах)
};


struct TObjectList: public TList {
    PTR _10;           ///< указатель на VMT класса итемов?
};

extern VMT_TList* vmt_TList;

extern void* (__fastcall* TObject_Create)    (VMT* cls, int8_t flag);

extern TList* (__fastcall* TList_Create)      (VMT_TList* cls, int8_t flag);
extern int(__fastcall* TList_Destroy)      (TList* list, int8_t flag);
extern void(__fastcall* TList_Add)         (TList* list, uint32_t value);
extern void(__fastcall* TList_Clear)       (TList* list);
extern void(__fastcall* TList_Delete)      (TList* list, int32_t index);
extern void(__fastcall* TList_Error)       (TList* list, int32_t, int32_t);
extern void(__fastcall* TList_Error_0)     (TList* list, int32_t, int32_t);
extern void(__fastcall* TList_Exchange)    (TList* list, int32_t index1, int32_t index2);
extern void(__fastcall* TList_Expand)      (TList* list);
extern uint32_t(__fastcall* TList_First)   (TList* list);
extern uint32_t(__fastcall* TList_Get)     (TList* list, int32_t index);
extern void(__fastcall* TList_Grow)        (TList* list);
extern int32_t(__fastcall* TList_IndexOf)  (TList* list, uint32_t value);
extern void(__fastcall* TList_Insert)      (TList* list, int32_t index, uint32_t value);
extern uint32_t(__fastcall* TList_Last)    (TList* list);
extern void(__fastcall* TList_Put)         (TList* list, int32_t index, uint32_t value);
extern void(__fastcall* TList_Remove)      (TList* list, uint32_t value);
extern void(__fastcall* TList_SetCapacity) (TList* list, int32_t new_capacity);
extern void(__fastcall* TList_SetCount)    (TList* list, int32_t new_count);
extern void(__fastcall* TList_Notify)      (TList* list);

namespace TListM
{
    void Init(TList* list);
    void Add(TList* list, void* object);
    void Delete(TList* list, int el_num);
};