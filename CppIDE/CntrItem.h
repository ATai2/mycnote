
// CntrItem.h: CCppIDECntrItem 类的接口
//

#pragma once

class CCppIDEDoc;
class CCppIDEView;

class CCppIDECntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CCppIDECntrItem)

// 构造函数
public:
	CCppIDECntrItem(REOBJECT* preo = nullptr, CCppIDEDoc* pContainer = nullptr);
		// 注意: 允许 pContainer 为 NULL 以启用 IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE 要求类具有带零
		//  参数的构造函数。  OLE 项通常是用
		//  非 null 文档指针

// 特性
public:
	CCppIDEDoc* GetDocument()
		{ return reinterpret_cast<CCppIDEDoc*>(CRichEditCntrItem::GetDocument()); }
	CCppIDEView* GetActiveView()
		{ return reinterpret_cast<CCppIDEView*>(CRichEditCntrItem::GetActiveView()); }

// 实现
public:
	~CCppIDECntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

