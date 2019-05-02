// dllmain.h: 模块类的声明。

class CMFCAppHandlersModule : public ATL::CAtlDllModuleT<CMFCAppHandlersModule>
{
public :
	DECLARE_LIBID(LIBID_MFCAppHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MFCAPPHANDLERS, "{43f9ccf1-d794-425b-a26e-6578534aa1c9}")
};

extern class CMFCAppHandlersModule _AtlModule;
