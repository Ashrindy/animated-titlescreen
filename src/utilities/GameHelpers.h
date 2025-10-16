#pragma once

template<typename T>
void registerRFL() {
    hh::fnd::RflClassNameRegistry::GetInstance()->Register(&T::rflClass);
    hh::fnd::RflTypeInfoRegistry::GetInstance()->Register(&T::rflTypeInfo);
}

#define ENUM_MEM(index, name) { index, #name, #name }

#define CAPTION_ATTRIBUTE(NAME) \
    static const char* NAME##Caption = #NAME; \
    static const RflCustomAttribute NAME##Attributes_[] = { \
        { "Caption", &NAME##Caption, nullptr } \
    }; \
    static const RflCustomAttributes NAME##Attributes = { \
        NAME##Attributes_, sizeof(NAME##Attributes_) / sizeof(RflCustomAttribute) \
    };

#define RFL_MEMBER(NAME, STRUCTNAME, TYPE) { #NAME, nullptr, nullptr, RflClassMember::Type::TYPE, RflClassMember::Type::VOID, 0, 0, offsetof(STRUCTNAME, NAME), &NAME##Attributes }
#define RFL_MEMBER_ARRAY(NAME, STRUCTNAME, TYPE, SIZE) { #NAME, nullptr, nullptr, RflClassMember::Type::TYPE, RflClassMember::Type::VOID, SIZE, 0, offsetof(STRUCTNAME, NAME), &NAME##Attributes }

#define RFL_CLASS(NAME) \
    const hh::fnd::RflClass NAME::rflClass{ \
        #NAME, \
        nullptr, \
        sizeof(NAME), \
        nullptr, \
        0, \
        members, \
        sizeof(members) / sizeof(hh::fnd::RflClassMember), \
        nullptr, \
    };

#define RFL_CLASS_WENUM(NAME) \
    const hh::fnd::RflClass NAME::rflClass{ \
        #NAME, \
        nullptr, \
        sizeof(NAME), \
        spawnerEnums, \
        sizeof(spawnerEnums) / sizeof(hh::fnd::RflClassEnum), \
        spawnerMembers, \
        sizeof(spawnerMembers) / sizeof(hh::fnd::RflClassMember), \
        nullptr, \
    };

#define RFL_TYPE_INFO_FUNCS(NAME, CONSTRUCT_BODY) \
    void* construct##NAME(void* instance, csl::fnd::IAllocator* allocator) { \
        auto* self = static_cast<NAME*>(instance); \
        CONSTRUCT_BODY \
        return self; \
    } \
    void finish##NAME(void* instance) {} \
    void clean##NAME(void* instance) {}

#define RFL_TYPE_INFO_FUNCS_CLEAN(NAME, CONSTRUCT_BODY, CLEAN_BODY) \
    void* construct##NAME(void* instance, csl::fnd::IAllocator* allocator) { \
        auto* self = static_cast<NAME*>(instance); \
        CONSTRUCT_BODY \
        return self; \
    } \
    void finish##NAME(void* instance) {\
        auto* self = static_cast<NAME*>(instance); \
        CLEAN_BODY \
    } \
    void clean##NAME(void* instance) {}

#define RFL_TYPE_INFO(NAME) \
    const hh::fnd::RflTypeInfo NAME::rflTypeInfo{ \
        #NAME, \
        #NAME, \
        construct##NAME, \
        finish##NAME, \
        clean##NAME, \
        sizeof(NAME), \
    };

#define GAMEOBJECT_CLASS(NAME) \
    const hh::game::GameObjectClass NAME##::gameObjectClass{ \
        #NAME, \
        #NAME, \
        sizeof(NAME), \
        &NAME##::Create, \
        0, \
        nullptr, \
        nullptr, \
    }; \
    const hh::game::GameObjectClass* NAME##::GetClass(){ \
        return &gameObjectClass; \
    }
