// dllmain.cpp: DllMain 的实现。

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "CppIDEHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CCppIDEHandlersModule _AtlModule;

class CCppIDEHandlersApp : public CWinApp
{
public:

// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CCppIDEHandlersApp, CWinApp)
END_MESSAGE_MAP()

CCppIDEHandlersApp theApp;

BOOL CCppIDEHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, nullptr))
		return FALSE;
	return CWinApp::InitInstance();
}

int CCppIDEHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
