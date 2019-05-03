
// CppIDEView.cpp: CCppIDEView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CppIDE.h"
#endif

#include "CppIDEDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "CppIDEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCppIDEView

IMPLEMENT_DYNCREATE(CCppIDEView, CRichEditView)

BEGIN_MESSAGE_MAP(CCppIDEView, CRichEditView)
	ON_WM_DESTROY()
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCppIDEView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCppIDEView 构造/析构

CCppIDEView::CCppIDEView() noexcept
{
	EnableActiveAccessibility();
	// TODO: 在此处添加构造代码

}

CCppIDEView::~CCppIDEView()
{
}

BOOL CCppIDEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CRichEditView::PreCreateWindow(cs);
}

void CCppIDEView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// 设置打印边距(720 缇 = 1/2 英寸)
	SetMargins(CRect(720, 720, 720, 720));
}


// CCppIDEView 打印


void CCppIDEView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCppIDEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}


void CCppIDEView::OnDestroy()
{
	// 析构时停用此项；这在
	// 使用拆分器视图时非常重要 
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != nullptr && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == nullptr);
   }
   CRichEditView::OnDestroy();
}


void CCppIDEView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCppIDEView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCppIDEView 诊断

#ifdef _DEBUG
void CCppIDEView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CCppIDEView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CCppIDEDoc* CCppIDEView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCppIDEDoc)));
	return (CCppIDEDoc*)m_pDocument;
}
#endif //_DEBUG


// CCppIDEView 消息处理程序
