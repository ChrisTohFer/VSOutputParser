#pragma once
#include <afxdockablepane.h>

#include "LibrariesPane.h"
#include "VerboseParser/Parser.h"

class ProjectPane : public CDockablePane
{
	DECLARE_DYNAMIC(ProjectPane)

public:
	ProjectPane(LibrariesPane* pane) : m_libraries_pane(pane){}

protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnSelChange();

	void SetProjects(std::vector<VERBOSE::PROJECT_KEY>);
	void ClearProjects();

	CListBox m_wndBox;
	std::vector<VERBOSE::PROJECT_KEY> m_projects;
	LibrariesPane* m_libraries_pane;
};

