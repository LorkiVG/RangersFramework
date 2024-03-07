#include "VMT.h"

using namespace std;

VMT_helper* vmt_struct(VMT vmt)
{
    return (VMT_helper*)((std::uint8_t*)vmt + vmt_base_offset);
}

void* SelfPtr(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->self_ptr; }
void* IntfTable(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->intf_table; }
void* AutoTable(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->auto_table; }
void* InitTable(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->init_table; }
void* TypeInfo(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->type_info; }
void* FieldTable(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->field_table; }
void* MethodTable(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->method_table; }
void* DynamicTable(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->dynamic_table; }
void* SafeCallException(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->safe_call_exception; }
void* AfterConstruction(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->after_construction; }
void* BeforeDestruction(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->before_destruction; }
void* Dispatch(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->dispatch; }
void* DefaultHandler(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->default_handler; }
void* NewInstance(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->new_instance; }
void* FreeInstance(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->free_instance; }
void* Destroy(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->destroy; }
uint32_t InstanceSize(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->instance_size; }
VMT   Parent(VMT vmt) { add_class(vmt); return vmt_struct(vmt)->parent; }
void* Method(VMT vmt, int index) { add_class(vmt); return vmt_struct(vmt)->methods[index]; }

bool IsSubClass(VMT child, VMT parent)
{
    add_class(child);
    add_class(parent);
    if (child == nullptr) return false;
    if (parent == nullptr) return false;
    if (child == parent) return true;
    return IsSubClass(Parent(child), parent);
}

template<class T>
bool IsInstance(T* obj, VMT cls)
{
    add_class(cls);
    if (obj == nullptr) return false;
    add_class(obj->cls);
    return IsSubClass(obj->cls, cls);
}

std::string ClassName(VMT vmt)
{
    int len = *vmt_struct(vmt)->class_name;
    char* src_str = (char*)(vmt_struct(vmt)->class_name + 1);
    char* copy_str = new char[len + 1];
    for (int i = 0; i < len; ++i) copy_str[i] = src_str[i];
    copy_str[len] = 0;
    return std::string(copy_str);
}

VMT get_class(const std::string& name)
{
    for (int i = 0; i < class_list.size(); ++i)
    {
        if (class_list[i].name == name)
        {
            return class_list[i].vmt;
        }
    }
    return 0;
}

void add_class(VMT vmt)
{
    if (vmt == nullptr) return;
    //if(vmt_set.find(vmt) != vmt_set.end()) return; //    
    if (get_class(ClassName(vmt))) return; //    
    //vmt_set.insert(vmt);
    //class_name_to_vmt[ClassName(vmt)] = vmt;
    class_list.push_back(VMT_index{ ClassName(vmt), vmt });
    //add_class(Parent(vmt));
}

std::vector<VMT_index> class_list = {};

TScriptShip* (__fastcall* TScriptShip_Create) (VMT*, int8_t flag) = nullptr;
int(__fastcall* TScriptShip_Destroy) (TScriptShip* list, int8_t flag) = nullptr;

TScriptShip* (__fastcall* TScriptShip_New) (VMT*) = nullptr;
void* (__fastcall* GetMem) (int) = nullptr;
void(__fastcall* FreeMem) (void*) = nullptr;

unordered_map<string, VMT> class_name_to_vmt = {};
unordered_set<VMT> vmt_set = {};