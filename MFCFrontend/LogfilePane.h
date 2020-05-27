#pragma once
#include <afxdockablepane.h>


class LogfilePane : public CDockablePane
{
	DECLARE_DYNAMIC(LogfilePane)

protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnSelChange();

	CListBox m_wndBox;

};

