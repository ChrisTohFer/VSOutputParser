#include "pch.h"
#include "LibrariesPane.h"
#include "LibraryDetailsDialog.h"

#include "VerboseParser/Parser.h"

IMPLEMENT_DYNAMIC(LibrariesPane, CDockablePane)

BEGIN_MESSAGE_MAP(LibrariesPane, CDockablePane)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_CONTROL(LBN_SELCHANGE, 5, &LibrariesPane::OnSelChange)
END_MESSAGE_MAP()

int LibrariesPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	DWORD style = LBS_NOTIFY | WS_BORDER | WS_VSCROLL | WS_CHILD | WS_VISIBLE;
	CRect rect(0, 0, 0, 0);
	if (!m_wndBox.Create(style, rect, this, 5))
		return -1;

	return 0;
}

void LibrariesPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndBox.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

void LibrariesPane::OnSelChange()
{
	LibraryDetailsDialog dialog;
	dialog.m_library = m_libraries[m_wndBox.GetCurSel()];
	dialog.DoModal();
}

void LibrariesPane::SetLibraries(std::vector<VERBOSE::LIBRARY> libraries)
{
	for (auto i = 0; i < libraries.size(); ++i)
	{
		m_wndBox.AddString(CString((libraries[i].name.c_str())));
	}

	m_libraries = std::move(libraries);
}

void LibrariesPane::ClearLibraries()
{
	m_libraries.clear();
	m_wndBox.ResetContent();
}
