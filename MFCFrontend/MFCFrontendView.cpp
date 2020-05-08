
// MFCFrontendView.cpp : implementation of the CMFCFrontendView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCFrontend.h"
#endif

#include "MFCFrontendDoc.h"
#include "MFCFrontendView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCFrontendView

IMPLEMENT_DYNCREATE(CMFCFrontendView, CView)

BEGIN_MESSAGE_MAP(CMFCFrontendView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCFrontendView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCFrontendView construction/destruction

CMFCFrontendView::CMFCFrontendView() noexcept
{
	// TODO: add construction code here

}

CMFCFrontendView::~CMFCFrontendView()
{
}

BOOL CMFCFrontendView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCFrontendView drawing

void CMFCFrontendView::OnDraw(CDC* /*pDC*/)
{
	CMFCFrontendDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCFrontendView printing


void CMFCFrontendView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCFrontendView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCFrontendView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCFrontendView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCFrontendView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCFrontendView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCFrontendView diagnostics

#ifdef _DEBUG
void CMFCFrontendView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCFrontendView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCFrontendDoc* CMFCFrontendView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCFrontendDoc)));
	return (CMFCFrontendDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCFrontendView message handlers
