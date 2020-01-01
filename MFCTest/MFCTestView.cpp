
// MFCTestView.cpp : implementation of the CMFCTestView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCTest.h"
#endif

#include "MFCTestDoc.h"
#include "MFCTestView.h"
#include "ParseFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTestView

IMPLEMENT_DYNCREATE(CMFCTestView, CView)

BEGIN_MESSAGE_MAP(CMFCTestView, CView)
	ON_COMMAND(ID_FILE_PARSESINGLEFILE, &CMFCTestView::OnFileParsesinglefile)
END_MESSAGE_MAP()

// CMFCTestView construction/destruction

CMFCTestView::CMFCTestView() noexcept
{
	// TODO: add construction code here

}

CMFCTestView::~CMFCTestView()
{
}

BOOL CMFCTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCTestView drawing

void CMFCTestView::OnDraw(CDC* /*pDC*/)
{
	CMFCTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCTestView diagnostics

#ifdef _DEBUG
void CMFCTestView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTestDoc* CMFCTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTestDoc)));
	return (CMFCTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTestView message handlers


void CMFCTestView::OnFileParsesinglefile()
{
	ParseFileDialog parseDialog;
	parseDialog.DoModal();
}
