#pragma once
#include <afxdockablepane.h>

#include "VerboseParser/Parser.h"

class LibrariesPane : public CDockablePane
{
	DECLARE_DYNAMIC(LibrariesPane)

protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnSelChange();

	void SetLibraries(std::vector<VERBOSE::LIBRARY>);
	void ClearLibraries();

	CListBox m_wndBox;
	std::vector<VERBOSE::LIBRARY> m_libraries;
};

