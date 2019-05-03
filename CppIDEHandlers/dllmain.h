// dllmain.h: 模块类的声明。

class CCppIDEHandlersModule : public ATL::CAtlDllModuleT<CCppIDEHandlersModule>
{
public :
	DECLARE_LIBID(LIBID_CppIDEHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CPPIDEHANDLERS, "{35641ce4-c3b2-4d4f-b243-f0a319fa4daf}")
};

extern class CCppIDEHandlersModule _AtlModule;
