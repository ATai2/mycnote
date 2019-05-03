
// CppIDEView.h: CCppIDEView 类的接口
//

#pragma once

class CCppIDECntrItem;

class CCppIDEView : public CRichEditView
{
protected: // 仅从序列化创建
	CCppIDEView() noexcept;
	DECLARE_DYNCREATE(CCppIDEView)

// 特性
public:
	CCppIDEDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCppIDEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnDestroy();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CppIDEView.cpp 中的调试版本
inline CCppIDEDoc* CCppIDEView::GetDocument() const
   { return reinterpret_cast<CCppIDEDoc*>(m_pDocument); }
#endif

