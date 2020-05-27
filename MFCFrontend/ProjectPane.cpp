#include "pch.h"
#include "ProjectPane.h"

#include "VerboseParser/Parser.h"

IMPLEMENT_DYNAMIC(ProjectPane, CDockablePane)

BEGIN_MESSAGE_MAP(ProjectPane, CDockablePane)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_CONTROL(LBN_SELCHANGE, 4, &ProjectPane::OnSelChange)
END_MESSAGE_MAP()

int ProjectPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	DWORD style = LBS_MULTIPLESEL | LBS_NOTIFY | WS_CHILD | WS_VISIBLE;
	CRect rect(0, 0, 0, 0);
	if (!m_wndBox.Create(style, rect, this, 4))
		return -1;

	return 0;
}

void ProjectPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndBox.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

void ProjectPane::OnSelChange()
{
	m_libraries_pane->ClearLibraries();

	std::vector<VERBOSE::PROJECT_KEY> selected_projects;

	//Get the selected logs
	{
		auto n = m_wndBox.GetSelCount();
		auto indicies = new int[n];
		m_wndBox.GetSelItems(n, indicies);

		for (auto i = 0; i < n; ++i)
			selected_projects.push_back(m_projects[indicies[i]]);

		delete[] indicies;
	}

	auto libraries = VERBOSE::libraries(std::move(selected_projects));
	m_libraries_pane->SetLibraries(std::move(libraries));
}

void ProjectPane::SetProjects(std::vector<VERBOSE::PROJECT_KEY> projects)
{
	for (auto i = 0; i < projects.size(); ++i)
	{
		m_wndBox.AddString(CString(projects[i].name.c_str()));
	}

	m_projects = std::move(projects);
}

void ProjectPane::ClearProjects()
{
	m_projects.clear();
	m_wndBox.ResetContent();
	m_libraries_pane->ClearLibraries();
}
