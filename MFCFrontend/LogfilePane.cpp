#include "pch.h"
#include "LogfilePane.h"

IMPLEMENT_DYNAMIC(LogfilePane, CDockablePane)

BEGIN_MESSAGE_MAP(LogfilePane, CDockablePane)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_CONTROL(LBN_SELCHANGE, 3, &LogfilePane::OnSelChange)
END_MESSAGE_MAP()

int LogfilePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	DWORD style = LBS_STANDARD | LBS_HASSTRINGS | LBS_MULTIPLESEL | LBS_NOTIFY | WS_CHILD | WS_VISIBLE;
	CRect rect(0, 0, 0, 0);
	if (!m_wndBox.Create(style, rect, this, 3))
		return -1;

	return 0;
}

void LogfilePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndBox.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

void LogfilePane::OnSelChange()
{

}