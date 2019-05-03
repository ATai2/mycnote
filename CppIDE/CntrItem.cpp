
// CntrItem.cpp: CCppIDECntrItem 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CppIDE.h"

#include "CppIDEDoc.h"
#include "CppIDEView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCppIDECntrItem 实现

IMPLEMENT_SERIAL(CCppIDECntrItem, CRichEditCntrItem, 0)

CCppIDECntrItem::CCppIDECntrItem(REOBJECT* preo, CCppIDEDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: 在此添加一次性构造代码
}

CCppIDECntrItem::~CCppIDECntrItem()
{
	// TODO: 在此处添加清理代码
}


// CCppIDECntrItem 诊断

#ifdef _DEBUG
void CCppIDECntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CCppIDECntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

