
// MFCTestView.h : interface of the CMFCTestView class
//

#pragma once


class CMFCTestView : public CView
{
protected: // create from serialization only
	CMFCTestView() noexcept;
	DECLARE_DYNCREATE(CMFCTestView)

// Attributes
public:
	CMFCTestDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileParsesinglefile();
};

#ifndef _DEBUG  // debug version in MFCTestView.cpp
inline CMFCTestDoc* CMFCTestView::GetDocument() const
   { return reinterpret_cast<CMFCTestDoc*>(m_pDocument); }
#endif

