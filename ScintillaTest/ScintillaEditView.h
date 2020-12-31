#pragma once


// CScintillaEditView 视图

class CScintillaEditView : public CView
{
	DECLARE_DYNCREATE(CScintillaEditView)

protected:
	CScintillaEditView();           // 动态创建所使用的受保护的构造函数
	virtual ~CScintillaEditView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
    afx_msg void OnPaint();
};


