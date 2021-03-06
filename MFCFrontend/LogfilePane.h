#pragma once
#include <afxdockablepane.h>

#include "ProjectPane.h"


class LogfilePane : public CDockablePane
{
	DECLARE_DYNAMIC(LogfilePane)

public:
	LogfilePane(ProjectPane* pane) : m_project_pane(pane){}

protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnSelChange();

	CListBox m_wndBox;
	ProjectPane* m_project_pane;
};

