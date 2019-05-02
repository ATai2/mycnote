// dllmain.cpp: DllMain 的实现。

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "MFCAppHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CMFCAppHandlersModule _AtlModule;

class CMFCAppHandlersApp : public CWinApp
{
public:

// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMFCAppHandlersApp, CWinApp)
END_MESSAGE_MAP()

CMFCAppHandlersApp theApp;

BOOL CMFCAppHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, nullptr))
		return FALSE;
	return CWinApp::InitInstance();
}

int CMFCAppHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
